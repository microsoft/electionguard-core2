using System;
using CommandLine;

namespace ElectionGuard.CLI.Encrypt;

[Verb("verify", HelpText = "Verify an Electionguard election record.")]
internal class VerifyOptions
{
    [Option('f', "file", Required = true, HelpText = "Zipfile contining an election record")]
    public string? ZipFile { get; set; }

    public void Validate()
    {
        ValidateFiles();
    }

    private void ValidateFiles()
    {
        var requiredFiles = new[] { ZipFile };
        var missingFiles = requiredFiles.Where(f => !File.Exists(f));
        foreach (var file in missingFiles)
        {
            throw new ArgumentException($"{file} does not exist");
        }
    }
}
