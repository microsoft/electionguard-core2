// DO NOT MODIFY THIS FILE
// This file is generated via ElectionGuard.InteropGenerator at /src/interop-generator

using System;
using System.Runtime.InteropServices;
using System.Runtime.ConstrainedExecution;

namespace ElectionGuard
{
    public partial class PlaintextBallotSelection
    {
        internal External.PlaintextBallotSelectionHandle Handle;

        #region Properties

        /// <Summary>
        /// Get the objectId of the selection which is the unique id for the selection in a specific contest described in the election manifest.
        /// </Summary>
        public string ObjectId
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
        /// Determines if this is a placeholder selection
        /// </Summary>
        public bool IsPlaceholder
        {
            get
            {
                return External.GetIsPlaceholder(Handle);
            }
        }

        /// <Summary>
        /// Get the plaintext vote
        /// </Summary>
        public ulong Vote
        {
            get
            {
                return External.GetVote(Handle);
            }
        }

        /// <Summary>
        /// An optional field of arbitrary data, such as the value of a write-in candidate
        /// </Summary>
        public ExtendedData ExtendedData
        {
            get
            {
                var status = External.GetExtendedData(
                    Handle, out NativeInterface.ExtendedData.ExtendedDataHandle value);
                status.ThrowIfError();
                if (value.IsInvalid)
                {
                    return null;
                }
                return new ExtendedData(value);
            }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Given a PlaintextBallotSelection validates that the object matches an expected object and that the plaintext value can resolve to a valid representation
        /// </summary>
        public bool IsValid(
            string expectedObjectId
        )
        {
            return External.IsValid(
                Handle, expectedObjectId);
        }


#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
        protected override void DisposeUnmanaged()
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
        {
            base.DisposeUnmanaged();

            if (Handle == null || Handle.IsInvalid) return;
            Handle.Dispose();
            Handle = null;
        }
        #endregion

        #region Extern

        internal static unsafe class External
        {
            internal struct PlaintextBallotSelectionType { };

            internal class PlaintextBallotSelectionHandle : ElectionGuardSafeHandle<PlaintextBallotSelectionType>
            {
#if NETSTANDARD
                [ReliabilityContract(Consistency.WillNotCorruptState, Cer.MayFail)]
#endif
                protected override bool Free()
                {
                    // releasing the C++ memory is currently handled by a parent object e.g. ballot, see https://github.com/microsoft/electionguard-core2/issues/29
                    return true;
                }
            }

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_selection_free",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern Status Free(PlaintextBallotSelectionType* handle);

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_selection_get_object_id",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern Status GetObjectId(
                PlaintextBallotSelectionHandle handle,
                out IntPtr objectId
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_selection_get_is_placeholder",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern bool GetIsPlaceholder(
                PlaintextBallotSelectionHandle handle
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_selection_get_vote",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern ulong GetVote(
                PlaintextBallotSelectionHandle handle
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_selection_get_extended_data",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern Status GetExtendedData(
                PlaintextBallotSelectionHandle handle,
                out NativeInterface.ExtendedData.ExtendedDataHandle objectId
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_selection_is_valid",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern bool IsValid(
                PlaintextBallotSelectionHandle handle,
                [MarshalAs(UnmanagedType.LPStr)] string expectedObjectId
                );

        }
        #endregion
    }
}
