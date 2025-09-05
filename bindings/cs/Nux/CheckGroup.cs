// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class CheckGroup
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_check_group_create();

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_check_group_destroy(IntPtr check_group);

        public CheckGroup()
        {
            _nux_check_group_v = nux_check_group_create();
        }

        ~CheckGroup()
        {
            nux_check_group_destroy(_nux_check_group_v);
        }

        internal IntPtr _nux_check_group_v;
    }
}
