﻿using System.IO.Compression;
using System.Text.Json;
using MongoDB.Driver;
using ElectionGuard.Decryption.ElectionRecord;
using Newtonsoft.Json;

namespace ElectionGuard.UI.Helpers;

public class ElectionRecordGenerator
{
    public static async Task GenerateElectionRecordAsync(TallyRecord tally, string outputFolder)
    {
        ArgumentException.ThrowIfNullOrEmpty(nameof(outputFolder));

        // check the state of the tally
        if (tally.State != TallyState.Complete)
        {
            throw new ArgumentException("The tally must be completed before generating an election record.");
        }

        // generate temp path to export all of the files to
        var tempFolder = Directory.CreateTempSubdirectory(ElectionRecordManager.FOLDER_PREFIX);

        // export the guardians
        await ExportGuardiansAsync(Path.Combine(tempFolder.FullName, ElectionRecordManager.GUARDIAN_FOLDER), tally.KeyCeremonyId!);

        // export the devices
        await ExportDevices(Path.Combine(tempFolder.FullName, ElectionRecordManager.DEVICE_FOLDER), tally.ElectionId!);

        // export the ballots
        await ExportBallotsAsync(Path.Combine(tempFolder.FullName, ElectionRecordManager.BALLOT_FOLDER), tally.ElectionId!);

        // export the challenged ballots v2 / spoiled ballots v1
        await ExportChallengedBallotsAsync(Path.Combine(tempFolder.FullName, ElectionRecordManager.CHALLENGED_FOLDER), tally.ElectionId!);

        // export the top level
        await ExportSummaryAsync(tempFolder.FullName, tally.ElectionId!, tally.TallyId);

        // create the zip from the folder
        var zipFile = Path.Combine(outputFolder, tally.Name!.Replace(" ", "_") + ".zip");
        if (File.Exists(zipFile))
        {
            File.Delete(zipFile); // TODO: consent for delete
        }

        ZipFile.CreateFromDirectory(tempFolder.FullName, zipFile);

        // delete the temp folder1
        Directory.Delete(tempFolder.FullName, true);
    }

    private static async Task ExportGuardiansAsync(string guardianFolder, string keyCeremonyId)
    {
        Directory.CreateDirectory(guardianFolder);

        // get all of the guardians public keys using key ceremony id
        GuardianPublicKeyService guardianPublicKeyService = new();
        var guardians = await guardianPublicKeyService.GetAllByKeyCeremonyIdAsync(keyCeremonyId);
        foreach (var guardian in guardians)
        {
            await File.WriteAllTextAsync(Path.Combine(guardianFolder, $"{ElectionRecordManager.GUARDIAN_PREFIX}{guardian.GuardianId}.json"), JsonConvert.SerializeObject(guardian.PublicKey));
        }
    }

    private static async Task ExportDevices(string deviceFolder, string electionId)
    {
        Directory.CreateDirectory(deviceFolder);

        // loop thru all ballot exports
        BallotUploadService ballotUploadService = new();
        var ballotUploads = await ballotUploadService.GetByElectionIdAsync(electionId);
        // export device file
        foreach (var upload in ballotUploads)
        {
            using var device = new EncryptionDevice((ulong)upload.DeviceId, (ulong)upload.SessionId, (ulong)upload.LaunchCode, upload.Location);
            await File.WriteAllTextAsync(Path.Combine(deviceFolder, $"{ElectionRecordManager.DEVICE_PREFIX}{upload.DeviceId}.json"), device.ToJson());
        }
    }

    private static async Task ExportBallotsAsync(string ballotFolder, string electionId)
    {
        Directory.CreateDirectory(ballotFolder);

        BallotService ballotService = new();
        using var cursor = await ballotService.GetCursorByElectionIdAsync(electionId);

        await cursor.ForEachAsync(document =>
        {
            var ballotCode = document.BallotCode;
            var fileName = $"{ballotCode}.json";
            var filePath = Path.Combine(ballotFolder, fileName);

            using var writer = new StreamWriter(filePath);
            var json = document.BallotData;
            writer.WriteLine(json);
        });
    }

    private static async Task ExportChallengedBallotsAsync(string ballotFolder, string electionId)
    {
        Directory.CreateDirectory(ballotFolder);

        BallotService ballotService = new();
        ChallengedBallotService challengedBallotService = new();
        using var cursor = await challengedBallotService.GetCursorByElectionIdAsync(electionId);

        await cursor.ForEachAsync(async document =>
        {
            var ballotCode = document.BallotCode;
            var fileName = $"{ballotCode}.json";
            var filePath = Path.Combine(ballotFolder, fileName);

            using var writer = new StreamWriter(filePath);
            var json = document.BallotData;
            writer.WriteLine(json);
        });
    }

    private static async Task ExportSummaryAsync(string summaryFolder, string electionId, string tallyId)
    {
        // write manifest
        ManifestService manifestService = new();
        var manifest = await manifestService.GetByElectionIdAsync(electionId);
        await File.WriteAllTextAsync(Path.Combine(summaryFolder, ElectionRecordManager.MANIFEST_FILENAME), manifest);

        // write context
        ContextService contextService = new();
        var context = await contextService.GetByElectionIdAsync(electionId);
        await File.WriteAllTextAsync(Path.Combine(summaryFolder, ElectionRecordManager.CONTEXT_FILENAME), context);

        // write constants
        ConstantsService constantsService = new();
        var constants = await constantsService.GetByElectionIdAsync(electionId);
        await File.WriteAllTextAsync(Path.Combine(summaryFolder, ElectionRecordManager.CONSTANTS_FILENAME), constants);

        // write coefficients
        LagrangeCoefficientsService lagrangeCoefficientsService = new();
        var coefficients = await lagrangeCoefficientsService.GetByTallyIdAsync(tallyId);
        await File.WriteAllTextAsync(Path.Combine(summaryFolder, ElectionRecordManager.COEFFICIENTS_FILENAME), coefficients);

        // write plaintext tally
        PlaintextTallyService plaintextTallyService = new();
        var plaintextTally = await plaintextTallyService.GetByTallyIdAsync(tallyId);
        await File.WriteAllTextAsync(Path.Combine(summaryFolder, ElectionRecordManager.TALLY_FILENAME), plaintextTally);

        // write ciphertext tally
        CiphertextTallyService ciphertextTallyService = new();
        var ciphertextTally = await ciphertextTallyService.GetByTallyIdAsync(tallyId);
        await File.WriteAllTextAsync(Path.Combine(summaryFolder, ElectionRecordManager.ENCRYPTED_TALLY_FILENAME), ciphertextTally);
    }
}
