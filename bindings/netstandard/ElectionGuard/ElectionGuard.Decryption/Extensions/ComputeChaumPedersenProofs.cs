using ElectionGuard.Ballot;
using ElectionGuard.Decryption.Accumulation;
using ElectionGuard.Decryption.Challenge;
using ElectionGuard.Decryption.ChallengeResponse;
using ElectionGuard.Decryption.Tally;

namespace ElectionGuard.Decryption.Extensions;

/// <summary>
/// Extensions for computing Chaum-Pedersen proofs
/// </summary>
public static class ComputeChaumPedersenProofs
{

    /// <summary>
    /// Add proofs to the tally
    /// </summary>
    public static void AddProofs(
        this AccumulatedTally self,
        CiphertextTally tally,
        List<GuardianChallengeResponse> responses,
        bool skipValidation = false
    )
    {
        self.AddProofs(
             tally,
             responses.Select(x => x.Tally).ToList(),
             skipValidation
         );
    }

    /// <summary>
    /// Add proofs to the tally
    /// </summary>
    public static void AddProofs(
        this AccumulatedTally self,
        CiphertextTally tally,
        List<TallyChallengeResponse> responses,
        bool skipValidation = false
    )
    {
        foreach (var (contestId, contest) in self.Contests)
        {
            var contestResponses = responses.Select(
                x => x.Contests[contestId]).ToList();
            contest.AddProofs(
                tally.Contests[contestId],
                tally.Context,
                contestResponses,
                skipValidation
            );
        }
    }

    /// <summary>
    /// Add proofs to the collection of ballots
    /// </summary>
    public static void AddProofs(
       this List<AccumulatedBallot> self,
       List<CiphertextBallot> ballots,
       CiphertextElectionContext context,
       List<GuardianChallengeResponse> responses,
       bool skipValidation = false
   )
    {
        var ballotResponses = new Dictionary<string, List<BallotChallengeResponse>>();
        foreach (var response in responses)
        {
            foreach (var ballotChallengeResponse in response.Ballots)
            {
                if (!ballotResponses.ContainsKey(ballotChallengeResponse.ObjectId))
                {
                    ballotResponses.Add(ballotChallengeResponse.ObjectId, new List<BallotChallengeResponse>());
                }

                ballotResponses[ballotChallengeResponse.ObjectId].Add(ballotChallengeResponse);
            }
        }

        self.AddProofs(ballots, context, ballotResponses, skipValidation);
    }

    /// <summary>
    /// Add proofs to the collection of ballots
    /// </summary>
    public static void AddProofs(
        this List<AccumulatedBallot> self,
        List<CiphertextBallot> ballots,
        CiphertextElectionContext context,
        Dictionary<string, List<BallotChallengeResponse>> responses,
        bool skipValidation = false
    )
    {
        for (var i = 0; i < self.Count; i++)
        {
            var ballot = ballots[i];
            var ballotResponses = responses[ballot.ObjectId];
            self[i].AddProofs(
                ballot, context, ballotResponses, skipValidation);
        }
    }

    /// <summary>
    /// Add proofs to the ballot
    /// </summary>
    public static void AddProofs(
        this AccumulatedBallot self,
        CiphertextBallot ballot,
        CiphertextElectionContext context,
        List<BallotChallengeResponse> responses,
        bool skipValidation = false
    )
    {
        foreach (var (contestId, contest) in self.Contests)
        {
            var contestResponses = responses.Select(
                x => x.Contests[contestId]).ToList();
            contest.AddProofs(
                ballot.Contests.First(x => x.ObjectId == contestId),
                context,
                contestResponses,
                skipValidation
            );
        }
    }

    /// <summary>
    /// Add proofs to the contest
    /// </summary>
    public static void AddProofs(
        this AccumulatedContest self,
        ICiphertextContest contest,
        CiphertextElectionContext context,
        List<ContestChallengeResponse> responses,
        bool skipValidation = false)
    {
        foreach (var (selectionId, selection) in self.Selections)
        {
            var selectionResponses = responses.Select(
                x => x.Selections[selectionId]).ToList();
            var proof = selection.ComputeProof(
                contest.Selections
                    .First(x => x.ObjectId == selectionId),
                context,
                selectionResponses,
                skipValidation
            );
            selection.AddProof(proof);
        }
    }

    /// <summary>
    /// Compute a CP proof for the accumulated selection
    /// </summary>
    public static ChaumPedersenProof ComputeProof(
        this AccumulatedSelection self,
        ICiphertextSelection selection,
        CiphertextElectionContext context,
        List<SelectionChallengeResponse> responses,
        bool skipValidation = false)
    {
        return self.ComputeProof(
            selection,
            context.CryptoExtendedBaseHash,
            context.ElGamalPublicKey,
            responses,
            skipValidation
        );

    }

    /// <summary>
    /// Compute a CP proof for the accumulated selection
    /// </summary>
    public static ChaumPedersenProof ComputeProof(
        this AccumulatedSelection self,
        ICiphertextSelection selection,
        ElementModQ extendedHash,
        ElementModP elGamalPublicKey,
        List<SelectionChallengeResponse> responses,
        bool skipValidation = false)
    {
        return self.ComputeProof(
            selection.Ciphertext,
            extendedHash,
            elGamalPublicKey,
            responses,
            skipValidation
        );
    }

    /// <summary>
    /// Compute a CP proof for the accumulated selection
    /// </summary>
    public static ChaumPedersenProof ComputeProof(
        this AccumulatedSelection self,
        ElGamalCiphertext ciphertext,
        ElementModQ extendedHash,
        ElementModP elGamalPublicKey,
        List<SelectionChallengeResponse> responses,
        bool skipValidation = false)
    {
        using var challenge = SelectionChallenge.ComputeChallenge(
                    extendedHash,
                    elGamalPublicKey,
                    ciphertext,
                    self.Commitment,
                    self.Value);

        return self.ComputeProof(challenge, responses);
    }

    public static ChaumPedersenProof ComputeProof(
        this AccumulatedSelection self,
        ElementModQ challenge,
        List<SelectionChallengeResponse> responses)
    {
        // Equation (76) in v2.0.0
        // v = E vi mod q 
        var response = responses.Aggregate(
            new ElementModQ(Constants.ZERO_MOD_Q),
            (acc, response) => acc.AddModQ(response.Response));

        return new ChaumPedersenProof(
            self.Commitment,
            challenge,
            response
        );
    }
}
