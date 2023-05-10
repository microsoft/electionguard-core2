using System.Diagnostics;
using ElectionGuard.Decryption.Accumulation;
using ElectionGuard.Decryption.Challenge;
using ElectionGuard.Decryption.Shares;
using ElectionGuard.Decryption.Tally;
using ElectionGuard.ElectionSetup;
using ElectionGuard.Guardians;

namespace ElectionGuard.Decryption.ChallengeResponse;

/// <summary>
/// A challenge for a specific guardian to prove that a decryption share was generated correctly.
/// </summary>
public record GuardianChallengeResponse : DisposableRecordBase
{
    // TODO: tallyId?

    /// <summary>
    /// The object id of the guardian.
    /// </summary>
    public string GuardianId { get; init; }

    /// <summary>
    /// The sequence order of the guardian.
    /// </summary>
    public ulong SequenceOrder { get; init; }

    /// <summary>
    /// The offset used to generate the commitment.
    /// </summary>
    public ElementModP CommitmentOffset { get; init; }

    public TallyChallengeResponse Tally { get; init; }

    public List<BallotChallengeResponse> Ballots { get; init; }

    public GuardianChallengeResponse(
        IElectionGuardian guardian,
        ElementModP commitmentOffset,
        TallyChallengeResponse tally,
        List<BallotChallengeResponse>? ballots)
    {
        GuardianId = guardian.GuardianId;
        SequenceOrder = guardian.SequenceOrder;
        CommitmentOffset = new(commitmentOffset);
        Tally = tally;
        Ballots = ballots ?? new List<BallotChallengeResponse>();
    }

    public GuardianChallengeResponse(GuardianChallengeResponse other) : base(other)
    {
        GuardianId = other.GuardianId;
        SequenceOrder = other.SequenceOrder;
        CommitmentOffset = new(other.CommitmentOffset);
        Tally = new(other.Tally);
        Ballots = other.Ballots.Select(x => new BallotChallengeResponse(x)).ToList();
    }

    public bool IsValid(
       CiphertextTally tally,
       List<CiphertextBallot> ballots,
       GuardianShare share,
       GuardianChallenge challenge)
    {
        if (!Tally.IsValid(
            tally,
            CommitmentOffset,
            share.Tally,
            challenge.Tally))
        {
            return false;
        }

        for (var i = 0; i < Ballots.Count; i++)
        {
            var ballot = ballots[i];
            var ballotShare = share.Ballots[i];
            var ballotChallenge = challenge.Ballots[i];

            if (!Ballots[i].IsValid(
                ballot,
                CommitmentOffset,
                ballotShare,
                ballotChallenge))
            {
                Console.WriteLine($"Ballot {ballot.ObjectId} is invalid");
                return false;
            }
        }

        return true;
    }

    protected override void DisposeManaged()
    {
        base.DisposeManaged();
        Tally.Dispose();
        foreach (var ballot in Ballots)
        {
            ballot.Dispose();
        }
    }
}
