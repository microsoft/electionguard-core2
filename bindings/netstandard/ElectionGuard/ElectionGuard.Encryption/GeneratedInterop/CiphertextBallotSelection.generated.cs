// DO NOT MODIFY THIS FILE
// This file is generated via ElectionGuard.InteropGenerator at /src/interop-generator

using System;
using System.Runtime.InteropServices;
using System.Runtime.ConstrainedExecution;

namespace ElectionGuard
{
    public partial class CiphertextBallotSelection
    {
        internal unsafe External.CiphertextBallotSelectionHandle Handle;

        #region Properties
        /// <Summary>
        /// Get the objectId of the selection, which is the unique id for the selection in a specific contest described in the election manifest.
        /// </Summary>
        public unsafe string ObjectId
        {
            get
            {
                var status = External.GetObjectId(Handle, out IntPtr value);
                status.ThrowIfError();
                var data = Marshal.PtrToStringAnsi(value);
                NativeInterface.Memory.FreeIntPtr(value);
                return data;
            }
        }

        /// <Summary>
        /// Get the sequence order of the selection
        /// </Summary>
        public unsafe ulong SequenceOrder
        {
            get
            {
                return External.GetSequenceOrder(Handle);
            }
        }

        /// <Summary>
        /// Determines if this is a placeholder selection
        /// </Summary>
        public unsafe bool IsPlaceholder
        {
            get
            {
                return External.GetIsPlaceholder(Handle);
            }
        }

        /// <Summary>
        /// The hash of the string representation of the Selection Description from the election manifest
        /// </Summary>
        public unsafe ElementModQ DescriptionHash
        {
            get
            {
                var status = External.GetDescriptionHash(
                    Handle, out NativeInterface.ElementModQ.ElementModQHandle value);
                status.ThrowIfError();
                return new ElementModQ(value);
            }
        }

        /// <Summary>
        /// The encrypted representation of the vote field
        /// </Summary>
        public unsafe ElGamalCiphertext Ciphertext
        {
            get
            {
                var status = External.GetCiphertext(
                    Handle, out NativeInterface.ElGamalCiphertext.ElGamalCiphertextHandle value);
                status.ThrowIfError();
                return new ElGamalCiphertext(value);
            }
        }

        /// <Summary>
        /// The hash of the encrypted values
        /// </Summary>
        public unsafe ElementModQ CryptoHash
        {
            get
            {
                var status = External.GetCryptoHash(
                    Handle, out NativeInterface.ElementModQ.ElementModQHandle value);
                status.ThrowIfError();
                return new ElementModQ(value);
            }
        }

        /// <Summary>
        /// The nonce used to generate the encryption. Sensitive &amp; should be treated as a secret
        /// </Summary>
        public unsafe ElementModQ Nonce
        {
            get
            {
                var status = External.GetNonce(
                    Handle, out NativeInterface.ElementModQ.ElementModQHandle value);
                status.ThrowIfError();
                return new ElementModQ(value);
            }
        }

        /// <Summary>
        /// The proof that demonstrates the selection is an encryption of 0 or 1, and was encrypted using the `nonce`
        /// </Summary>
        public unsafe DisjunctiveChaumPedersenProof Proof
        {
            get
            {
                var status = External.GetProof(
                    Handle, out NativeInterface.DisjunctiveChaumPedersenProof.DisjunctiveChaumPedersenProofHandle value);
                status.ThrowIfError();
                return new DisjunctiveChaumPedersenProof(value);
            }
        }

        #endregion

        #region Methods

#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
        protected override unsafe void DisposeUnmanaged()
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
        {
            base.DisposeUnmanaged();

            if (Handle == null || Handle.IsInvalid) return;
            Handle.Dispose();
            Handle = null;
        }
        #endregion

        #region Extern
        internal unsafe static class External {
            internal unsafe struct CiphertextBallotSelectionType { };

            internal class CiphertextBallotSelectionHandle : ElectionGuardSafeHandle<CiphertextBallotSelectionType>
            {
                [ReliabilityContract(Consistency.WillNotCorruptState, Cer.MayFail)]
                protected override bool Free()
                {
                    // releasing the C++ memory is currently handled by a parent object e.g. ballot, see https://github.com/microsoft/electionguard-core2/issues/29
                    return true;
                }
            }

            [DllImport(NativeInterface.DllName, EntryPoint = "eg_ciphertext_ballot_selection_free",
                CallingConvention = CallingConvention.Cdecl, SetLastError = true)]
            internal static extern Status Free(CiphertextBallotSelectionType* handle);

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_object_id",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern Status GetObjectId(
                CiphertextBallotSelectionHandle handle
                , out IntPtr objectId
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_sequence_order",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern ulong GetSequenceOrder(
                CiphertextBallotSelectionHandle handle
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_is_placeholder",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern bool GetIsPlaceholder(
                CiphertextBallotSelectionHandle handle
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_description_hash",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern Status GetDescriptionHash(
                CiphertextBallotSelectionHandle handle
                , out NativeInterface.ElementModQ.ElementModQHandle objectId
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_ciphertext",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern Status GetCiphertext(
                CiphertextBallotSelectionHandle handle
                , out NativeInterface.ElGamalCiphertext.ElGamalCiphertextHandle objectId
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_crypto_hash",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern Status GetCryptoHash(
                CiphertextBallotSelectionHandle handle
                , out NativeInterface.ElementModQ.ElementModQHandle objectId
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_nonce",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern Status GetNonce(
                CiphertextBallotSelectionHandle handle
                , out NativeInterface.ElementModQ.ElementModQHandle objectId
            );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_ciphertext_ballot_selection_get_proof",
                CallingConvention = CallingConvention.Cdecl, 
                SetLastError = true
            )]
            internal static extern Status GetProof(
                CiphertextBallotSelectionHandle handle
                , out NativeInterface.DisjunctiveChaumPedersenProof.DisjunctiveChaumPedersenProofHandle objectId
            );

        }
        #endregion
    }
}