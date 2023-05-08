using ElectionGuard.Ballot;
using ElectionGuard.Decryption.Accumulation;
using ElectionGuard.ElectionSetup;
using ElectionGuard.ElectionSetup.Extensions;
using ElectionGuard.Guardians;

namespace ElectionGuard.Decryption.Challenge;

/// <summary>
/// The Decryption of a contest used when publishing the results of an election.
/// </summary>
public record BallotChallenge
    : DisposableRecordBase, IEquatable<BallotChallenge>
{
    /// <summary>
    /// The object id of the contest
    /// </summary>
    public string ObjectId { get; init; }

    /// <summary>
    /// The object id of the contest
    /// </summary>
    public string GuardianId { get; init; }

    // sequence order of the guardian
    public ulong SequenceOrder { get; init; }

    public ElementModQ Coefficient { get; init; }

    public Dictionary<string, ContestChallenge> Contests { get; init; } = default!;

    public BallotChallenge(
        IElectionGuardian guardian,
        LagrangeCoefficient coefficient,
        CiphertextBallot ballot,
        InternalManifest manifest)
    {
        if (guardian.SequenceOrder != coefficient.SequenceOrder)
        {
            throw new ArgumentException(
                $"Guardian sequence order {guardian.SequenceOrder} does not match coefficient sequence order {coefficient.SequenceOrder}");
        }
        ObjectId = ballot.ObjectId;
        GuardianId = guardian.GuardianId;
        SequenceOrder = guardian.SequenceOrder;
        Coefficient = coefficient.Coefficient;
        Contests = manifest
            .GetContests(ballot.StyleId)
            .ToContestChallengeDictionary();
    }

    public BallotChallenge(
        IElectionGuardian guardian,
        LagrangeCoefficient coefficient,
        CiphertextBallot ballot)
    {
        if (guardian.SequenceOrder != coefficient.SequenceOrder)
        {
            throw new ArgumentException(
                $"Guardian sequence order {guardian.SequenceOrder} does not match coefficient sequence order {coefficient.SequenceOrder}");
        }

        ObjectId = ballot.ObjectId;
        GuardianId = guardian.GuardianId;
        SequenceOrder = guardian.SequenceOrder;
        Coefficient = coefficient.Coefficient;
        Contests = ballot
            .ToContestChallengeDictionary();
    }

    public BallotChallenge(
        IElectionGuardian guardian,
        ElementModQ coefficient,
        AccumulatedBallot accumulated)
    {
        ObjectId = accumulated.ObjectId;
        GuardianId = guardian.GuardianId;
        SequenceOrder = guardian.SequenceOrder;
        Coefficient = coefficient;
        Contests = accumulated
            .ToContestChallengeDictionary();
    }

    public BallotChallenge(
        string guardianId,
        LagrangeCoefficient coefficient,
        CiphertextBallot ballot)
    {
        ObjectId = ballot.ObjectId;
        GuardianId = guardianId;
        SequenceOrder = coefficient.SequenceOrder;
        Coefficient = coefficient.Coefficient;
        Contests = ballot
            .ToContestChallengeDictionary();
    }

    public BallotChallenge(
        string guardianId,
        LagrangeCoefficient coefficient,
        AccumulatedBallot accumulated)
    {
        ObjectId = accumulated.ObjectId;
        GuardianId = guardianId;
        SequenceOrder = coefficient.SequenceOrder;
        Coefficient = coefficient.Coefficient;
        Contests = accumulated
            .ToContestChallengeDictionary();
    }

    public void Add(
        IElectionContest contest,
        SelectionChallenge selection)
    {
        Contests[contest.ObjectId].Add(selection);
    }

    public void Add(
        IElectionContest contest,
        IElectionSelection selection,
        ElementModQ challenge)
    {
        Contests[contest.ObjectId].Add(new SelectionChallenge(
            selection.ObjectId,
            GuardianId,
            SequenceOrder,
            Coefficient,
            challenge));
    }


    protected override void DisposeUnmanaged()
    {
        base.DisposeUnmanaged();
    }
}

public static partial class InternalManifestExtensions
{
    /// <summary>
    /// Converts an internal manifest to a dictionary of CiphertextTallyContest
    /// </summary>
    public static Dictionary<string, ContestChallenge> ToContestChallengeDictionary(
        this List<ContestDescriptionWithPlaceholders> contestDescriptions)
    {
        var contests = new Dictionary<string, ContestChallenge>();
        foreach (var contestDescription in contestDescriptions)
        {
            contests.Add(
                contestDescription.ObjectId,
                new ContestChallenge(contestDescription));
        }
        return contests;
    }
}

public static partial class CiphertextBallotExtensions
{
    /// <summary>
    /// Converts an internal manifest to a dictionary of CiphertextTallyContest
    /// </summary>
    public static Dictionary<string, ContestChallenge> ToContestChallengeDictionary(
        this CiphertextBallot ballot)
    {
        var contests = new Dictionary<string, ContestChallenge>();
        foreach (var contest in ballot.Contests)
        {
            contests.Add(
                contest.ObjectId,
                new ContestChallenge(contest));
        }
        return contests;
    }
}

public static partial class AccumulatedBallotExtensions
{
    /// <summary>
    /// Converts an internal manifest to a dictionary of CiphertextTallyContest
    /// </summary>
    public static Dictionary<string, ContestChallenge> ToContestChallengeDictionary(
        this AccumulatedBallot accumulated)
    {
        var contests = new Dictionary<string, ContestChallenge>();
        foreach (var (contestId, contest) in accumulated.Contests)
        {
            contests.Add(
                contest.ObjectId,
                new ContestChallenge(contest));
        }
        return contests;
    }
}


