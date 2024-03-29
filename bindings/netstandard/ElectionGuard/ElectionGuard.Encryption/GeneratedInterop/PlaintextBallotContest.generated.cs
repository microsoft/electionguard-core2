// DO NOT MODIFY THIS FILE
// This file is generated via ElectionGuard.InteropGenerator at /src/interop-generator

using System;
using System.Runtime.InteropServices;
using System.Runtime.ConstrainedExecution;

namespace ElectionGuard
{
    public partial class PlaintextBallotContest
    {
        internal External.PlaintextBallotContestHandle Handle;

        #region Properties

        /// <Summary>
        /// Get the objectId of the contest, which is the unique id for the contest in a specific ballot style described in the election manifest.
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
        /// Get the Size of the selections collection
        /// </Summary>
        public ulong SelectionsSize
        {
            get
            {
                return External.GetSelectionsSize(Handle);
            }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Given a PlaintextBallotContest returns true if the state is representative of the expected values.  Note: because this class supports partial representations, undervotes are considered a valid state.
        /// </summary>
        public bool IsValid(
            string expectedObjectId, ulong expectedNumSelections, ulong expectedNumElected, ulong votesAllowed = 0
        )
        {
            return External.IsValid(
                Handle, expectedObjectId, expectedNumSelections, expectedNumElected, votesAllowed);
        }

        /// <summary>
        /// Get a selection at a specific index.
        /// </summary>
        /// <param name="index">The index of the selection</param>
        public PlaintextBallotSelection GetSelectionAtIndex(
            ulong index
        )
        {
            var status = External.GetSelectionAtIndex(
                Handle,
                index,
                out PlaintextBallotSelection.External.PlaintextBallotSelectionHandle value);
            status.ThrowIfError();
            return new PlaintextBallotSelection(value);
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
            internal struct PlaintextBallotContestType { };

            internal class PlaintextBallotContestHandle : ElectionGuardSafeHandle<PlaintextBallotContestType>
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
                EntryPoint = "eg_plaintext_ballot_contest_free",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern Status Free(PlaintextBallotContestType* handle);

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_contest_get_object_id",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern Status GetObjectId(
                PlaintextBallotContestHandle handle,
                out IntPtr objectId
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_contest_get_selections_size",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern ulong GetSelectionsSize(
                PlaintextBallotContestHandle handle
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_contest_is_valid",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern bool IsValid(
                PlaintextBallotContestHandle handle,
                [MarshalAs(UnmanagedType.LPStr)] string expectedObjectId,
                ulong expectedNumSelections,
                ulong expectedNumElected,
                ulong votesAllowed
                );

            [DllImport(
                NativeInterface.DllName,
                EntryPoint = "eg_plaintext_ballot_contest_get_selection_at_index",
                CallingConvention = CallingConvention.Cdecl,
                SetLastError = true)]
            internal static extern Status GetSelectionAtIndex(
                PlaintextBallotContestHandle handle,
                ulong index,
                out PlaintextBallotSelection.External.PlaintextBallotSelectionHandle objectId
                );

        }
        #endregion
    }
}
