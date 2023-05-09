using System.Diagnostics;
using ElectionGuard.Ballot;

namespace ElectionGuard.ElectionSetup;

/// <summary>
/// methods for decrypting
/// </summary>
public partial class Guardian
{
    // (a𝑖, b𝑖) = (𝑔^𝑢𝑖 mod 𝑝, 𝐴^𝑢𝑖 mod 𝑝).
    public ElGamalCiphertext CreateCommitment(ICiphertextSelection selection)
    {
        if (AllGuardianKeysReceived is false)
        {
            throw new InvalidOperationException("All guardian keys must be received before decrypting.");
        }

        // create a nonce for the selection
        using var nonces = NonceForSelection(selection);
        using var u = nonces.Next();

        Debug.WriteLine($"CreateCommitment: {u}");

        using var a = BigMath.GPowP(u);  // 𝑔^𝑢𝑖 mod 𝑝
        using var b = BigMath.PowModP(selection.Ciphertext.Pad, u);  // 𝐴^𝑢𝑖 mod 𝑝

        return new ElGamalCiphertext(a, b);
    }

    // the challenge is the guardian-scoped challenge 
    // that has been adjusted by the lagrange coefficient
    public ElementModQ CreateResponse(
        IElectionSelection selection,
        ElementModQ challenge)
    {
        if (AllGuardianKeysReceived is false)
        {
            throw new InvalidOperationException("All guardian keys must be received before decrypting.");
        }

        // recreate the nonce for the selection
        using var nonces = NonceForSelection(selection);
        using var u = nonces.Next();

        Debug.WriteLine($"CreateResponse: {u}");

        // rehydrate the partial secret if it has not been done already
        if (_myPartialSecretKey is null)
        {
            Console.WriteLine($"CreateResponse: rehydrating partial secret key");
            _ = CombinePrivateKeyShares();
        }

        // TODO: double check the mul mod q here is not a problem
        // since its not a mod op in the spec

        // vi = (ui − ciP(i)) mod q.
        using var product = BigMath.MultModQ(challenge, _myPartialSecretKey);
        var v = BigMath.SubModQ(u, product);
        return v;
    }

    // create a nonce specific for the selection that is based on the guardian commitment seed
    private Nonces NonceForSelection(IElectionSelection selection)
    {
        using var selectionHash = Hash.HashElems(
            selection.ObjectId, selection.SequenceOrder, selection.DescriptionHash);
        using var hashSeed = Hash.HashElems(
            _commitmentSeed, selectionHash);

        // TODO: move this magic string to a constant
        return new Nonces(hashSeed, "chaum-pedersen-proof");
    }
}