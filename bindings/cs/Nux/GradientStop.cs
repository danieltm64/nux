// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class GradientStop
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_gradient_stop_create(float position, IntPtr color);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gradient_stop_destroy(IntPtr gradient_stop);

        public GradientStop(float position, GVector4D color)
        {
            _nux_gradient_stop_v = nux_gradient_stop_create(position, color._nux_gvector4d_v);
        }

        ~GradientStop()
        {
            nux_gradient_stop_destroy(_nux_gradient_stop_v);
        }

        internal IntPtr _nux_gradient_stop_v;
    }
}
