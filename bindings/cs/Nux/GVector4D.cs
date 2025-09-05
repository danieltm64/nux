// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class GVector4D
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_gvector4d_create(float x, float y, float z, float w);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector4d_destroy(IntPtr gvector4d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector4d_get_x(IntPtr gvector4d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector4d_set_x(IntPtr gvector4d, float new_x);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector4d_get_y(IntPtr gvector4d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector4d_set_y(IntPtr gvector4d, float new_y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector4d_get_z(IntPtr gvector4d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector4d_set_z(IntPtr gvector4d, float new_z);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector4d_get_w(IntPtr gvector4d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector4d_set_w(IntPtr gvector4d, float new_w);

        public GVector4D(float x, float y, float z, float w)
        {
            _nux_gvector4d_v = nux_gvector4d_create(x, y, z, w);
        }

        ~GVector4D()
        {
            nux_gvector4d_destroy(_nux_gvector4d_v);
        }

        public float X
        {
            get
            {
                return nux_gvector4d_get_x(_nux_gvector4d_v);
            }
            set
            {
                nux_gvector4d_set_x(_nux_gvector4d_v, value);
            }
        }

        public float Y
        {
            get
            {
                return nux_gvector4d_get_y(_nux_gvector4d_v);
            }
            set
            {
                nux_gvector4d_set_y(_nux_gvector4d_v, value);
            }
        }

        public float Z
        {
            get
            {
                return nux_gvector4d_get_z(_nux_gvector4d_v);
            }
            set
            {
                nux_gvector4d_set_z(_nux_gvector4d_v, value);
            }
        }

        public float W
        {
            get
            {
                return nux_gvector4d_get_w(_nux_gvector4d_v);
            }
            set
            {
                nux_gvector4d_set_w(_nux_gvector4d_v, value);
            }
        }

        internal IntPtr _nux_gvector4d_v;
    }
}
