using System.Collections.Generic;
using Newtonsoft.Json;

namespace ElectionGuard.Proofs
{

    /// <summary>
    /// Representation of a Schnorr proof
    /// </summary>
    public class SchnorrProof : DisposableBase
    {


        /// <summary>
        /// K in the spec
        /// </summary>
        public ElementModP PublicKey { get; private set; }

        /// <summary>
        /// h in the spec
        /// </summary>
        public ElementModP Commitment { get; private set; }

        /// <summary>
        /// c in the spec
        /// </summary>
        public ElementModQ Challenge { get; private set; }

        /// <summary>
        /// v in the spec
        /// </summary>
        public ElementModQ Response { get; private set; }

        public ProofUsage Usage = ProofUsage.SecretValue;

        [JsonConstructor]
        public SchnorrProof(
            ElementModP publicKey,
            ElementModP commitment,
            ElementModQ challenge,
            ElementModQ response)
        {
            PublicKey = new ElementModP(publicKey);
            Commitment = new ElementModP(commitment);
            Challenge = new ElementModQ(challenge);
            Response = new ElementModQ(response);
        }

        /// <summary>
        /// Create a new instance of a Schnorr proof using the provided secret and a random seed.
        /// </summary>
        public SchnorrProof(
            ulong offset,
            int index,
            ElementModQ parameterHash,
            ElementModQ secretKey)
        {
            using (var keyPair = ElGamalKeyPair.FromSecret(secretKey))
            using (var seed = BigMath.RandQ())
            {
                PublicKey = new ElementModP(keyPair.PublicKey);
                Commitment = BigMath.GPowP(seed);
                Challenge = ComputeChallenge(parameterHash, offset, index, PublicKey, Commitment);
                Response = BigMath.APlusBMulCModQ(seed, keyPair.SecretKey, Challenge);
            }
        }

        /// <summary>
        /// Create a new instance of a Schnorr proof using the provided key pair and a random seed.
        /// </summary>
        public SchnorrProof(
            ulong offset,
            int index,
            ElementModQ parameterHash,
            ElGamalKeyPair keyPair)
        {
            using (var seed = BigMath.RandQ())
            {
                PublicKey = new ElementModP(keyPair.PublicKey);
                Commitment = BigMath.GPowP(seed);
                Challenge = ComputeChallenge(parameterHash, offset, index, PublicKey, Commitment);
                Response = BigMath.APlusBMulCModQ(seed, keyPair.SecretKey, Challenge);
            }
        }

        /// <summary>
        /// Create a new instance of a Schnorr proof using the provided secret and seed.
        /// </summary>
        public SchnorrProof(
            ulong offset,
            int index,
            ElementModQ parameterHash,
            ElementModQ secretKey,
            ElementModQ seed)
        {
            using (var keyPair = ElGamalKeyPair.FromSecret(secretKey))
            {

                PublicKey = new ElementModP(keyPair.PublicKey);
                Commitment = BigMath.GPowP(seed);
                Challenge = ComputeChallenge(parameterHash, offset, index, PublicKey, Commitment);
                Response = BigMath.APlusBMulCModQ(seed, keyPair.SecretKey, Challenge);
            }
        }

        /// <summary>
        /// Create a new instance of a Schnorr proof using the provided key pair and seed.
        /// </summary>
        public SchnorrProof(
            ulong offset,
            int index,
            ElementModQ parameterHash,
            ElGamalKeyPair keyPair,
            ElementModQ seed)
        {
            PublicKey = new ElementModP(keyPair.PublicKey);
            Commitment = BigMath.GPowP(seed);
            Challenge = ComputeChallenge(parameterHash, offset, index, PublicKey, Commitment);
            Response = BigMath.APlusBMulCModQ(seed, keyPair.SecretKey, Challenge);
        }

        public SchnorrProof(SchnorrProof other)
        {
            PublicKey = new ElementModP(other.PublicKey);
            Commitment = new ElementModP(other.Commitment);
            Challenge = new ElementModQ(other.Challenge);
            Response = new ElementModQ(other.Response);
        }

        /// <summary>
        /// Verification 2 (Guardian public-key validation).
        /// Check validity of the `proof` for proving possession of the secret key 
        /// corresponding to the public key.
        /// </summary>     
        public ValidationResult IsValid(
            ulong offset,
            int index,
            ElementModQ parameterHash
        )
        {
            var k = PublicKey;
            var h = Commitment;
            var v = Response;
            var validPublicKey = k.IsValidResidue();
            var inBoundsH = h.IsInBounds();
            var inBoundsU = v.IsInBounds();

#pragma warning disable IDE0063 // Use simple 'using' statement. Need to support Net Standard 2.0, which doesn't have this.
            using (var c = ComputeChallenge(parameterHash, offset, index, k, h))
            using (var gp = BigMath.GPowP(v))
            using (var pp = BigMath.PowModP(k, c))
            using (var mp = BigMath.MultModP(h, pp))
#pragma warning restore IDE0063
            {

                var validChallenge = c.Equals(Challenge);
                var validProof = gp.Equals(mp);

                var messages = new List<string>();
                var success = validPublicKey && inBoundsH && inBoundsU && validChallenge && validProof;
                if (success is false)
                {

                    messages.Add("found an invalid Schnorr proof");
                    messages.Add($"in_bounds_h: {inBoundsH}");
                    messages.Add($"in_bounds_u: {inBoundsU}");
                    messages.Add($"valid_public_key: {validPublicKey}");
                    messages.Add($"valid_challenge: {validChallenge}");
                    messages.Add($"valid_proof: {validProof}");
                }
                return new ValidationResult() { Success = success, Error = messages };
            }
        }

        protected override void DisposeUnmanaged()
        {
            base.DisposeUnmanaged();

            PublicKey.Dispose();
            Commitment.Dispose();
            Challenge.Dispose();
            Response.Dispose();
        }

        /// <Summary>
        ///  H = (HP;10,i,j,Ki,j,hi,j). Guardin Share proof challenge 3.2.2
        /// </Summary>
        private ElementModQ ComputeChallenge(
            ElementModQ parameterHash,
            ulong offset,
            int index,
            ElementModP publicKey,
            ElementModP commitment)
        {
            using (var offsetElement = new ElementModQ(offset))
            using (var indexElement = new ElementModQ((ulong)index))
            {
                return Hash.HashElems(
                    parameterHash,
                    Hash.Prefix_GuardianShareChallenge,
                    offsetElement, indexElement,
                    publicKey, commitment);
            }
        }
    }
}
