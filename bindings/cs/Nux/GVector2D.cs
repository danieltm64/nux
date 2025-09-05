// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class GVector2D
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_gvector2d_create(float x, float y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector2d_destroy(IntPtr gvector2d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector2d_get_x(IntPtr gvector2d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector2d_set_x(IntPtr gvector2d, float new_x);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector2d_get_y(IntPtr gvector2d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector2d_set_y(IntPtr gvector2d, float new_y);

        public GVector2D(float x, float y)
        {
            _nux_gvector2d_v = nux_gvector2d_create(x, y);
        }

        ~GVector2D()
        {
            nux_gvector2d_destroy(_nux_gvector2d_v);
        }

        public float X
        {
            get
            {
                return nux_gvector2d_get_x(_nux_gvector2d_v);
            }
            set
            {
                nux_gvector2d_set_x(_nux_gvector2d_v, value);
            }
        }

        public float Y
        {
            get
            {
                return nux_gvector2d_get_y(_nux_gvector2d_v);
            }
            set
            {
                nux_gvector2d_set_y(_nux_gvector2d_v, value);
            }
        }

        internal IntPtr _nux_gvector2d_v;
    }
}
