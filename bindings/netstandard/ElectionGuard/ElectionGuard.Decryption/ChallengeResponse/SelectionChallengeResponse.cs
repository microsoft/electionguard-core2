﻿using ElectionGuard.Ballot;
using ElectionGuard.Decryption.Challenge;
using ElectionGuard.Decryption.Extensions;
using ElectionGuard.Decryption.Shares;
using ElectionGuard.ElectionSetup;
using ElectionGuard.Guardians;

namespace ElectionGuard.Decryption.ChallengeResponse;

/// <summary>
/// A response to a challenge for a specific selection.
/// </summary>
public record SelectionChallengeResponse : DisposableRecordBase
{
    /// <summary>
    /// The object id of the selection.
    /// </summary>
    public string ObjectId { get; init; }

    /// <summary>
    /// The id of the guardian.
    /// </summary>
    public string GuardianId { get; init; }

    /// <summary>
    /// The sequence order of the guardian
    /// </summary>
    public ulong SequenceOrder { get; init; }

    /// <summary>
    // The response to the challenge.
    ///
    // 𝑣𝑖 in the spec
    /// </summary>
    public ElementModQ Response { get; init; }

    [JsonConstructor]
    public SelectionChallengeResponse(
        string objectId,
        string guardianId,
        ulong sequenceOrder,
        ElementModQ response)
    {
        ObjectId = objectId;
        SequenceOrder = sequenceOrder;
        GuardianId = guardianId;
        Response = new(response);
    }

    public SelectionChallengeResponse(
        IElectionGuardian guardian,
        SelectionChallenge challenge,
        ElementModQ response)
    {
        ObjectId = challenge.ObjectId;
        SequenceOrder = guardian.SequenceOrder;
        GuardianId = guardian.GuardianId;
        Response = response;
    }

    public SelectionChallengeResponse(SelectionChallengeResponse other) : base(other)
    {
        ObjectId = other.ObjectId;
        SequenceOrder = other.SequenceOrder;
        GuardianId = other.GuardianId;
        Response = new(other.Response);
    }

    public bool IsValid(
        ICiphertextSelection selection,
        ElementModP commitmentOffset,
        SelectionShare share,
        SelectionChallenge challenge)
    {
        if (!ObjectId.Equals(selection.ObjectId)
            || !ObjectId.Equals(share.ObjectId)
            || !ObjectId.Equals(challenge.ObjectId))
        {
            Console.WriteLine($"SelectionChallengeResponse: Invalid object id: \n {ObjectId} \n {selection.ObjectId} \n {share.ObjectId} \n {challenge.ObjectId}");
            return false;
        }

        return IsValid(
            selection.Ciphertext,
            share.Commitment,
            challenge.Challenge,
            commitmentOffset,
            share.Share);
    }

    /// <summary>
    /// Verify the response to the challenge.
    /// </summary>
    public bool IsValid(
        ElGamalCiphertext ciphertext,
        ElGamalCiphertext commitment,
        ElementModQ challenge,
        ElementModP commitmentOffset,
        ElementModP m_i)
    {
        using var recomputedCommitment = this.ComputeCommitment(
            ciphertext.Pad,
            challenge,
            commitmentOffset,
            m_i);

        return recomputedCommitment.Equals(commitment);
    }

    protected override void DisposeUnmanaged()
    {
        base.DisposeUnmanaged();
        Response?.Dispose();
    }
}
