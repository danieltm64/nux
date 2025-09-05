// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class GVector3D
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_gvector3d_create(float x, float y, float z);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector3d_destroy(IntPtr gvector3d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector3d_get_x(IntPtr gvector3d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector3d_set_x(IntPtr gvector3d, float new_x);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector3d_get_y(IntPtr gvector3d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector3d_set_y(IntPtr gvector3d, float new_y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern float nux_gvector3d_get_z(IntPtr gvector3d);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_gvector3d_set_z(IntPtr gvector3d, float new_z);

        public GVector3D(float x, float y, float z)
        {
            _nux_gvector3d_v = nux_gvector3d_create(x, y, z);
        }

        ~GVector3D()
        {
            nux_gvector3d_destroy(_nux_gvector3d_v);
        }

        public float X
        {
            get
            {
                return nux_gvector3d_get_x(_nux_gvector3d_v);
            }
            set
            {
                nux_gvector3d_set_x(_nux_gvector3d_v, value);
            }
        }

        public float Y
        {
            get
            {
                return nux_gvector3d_get_y(_nux_gvector3d_v);
            }
            set
            {
                nux_gvector3d_set_y(_nux_gvector3d_v, value);
            }
        }

        public float Z
        {
            get
            {
                return nux_gvector3d_get_z(_nux_gvector3d_v);
            }
            set
            {
                nux_gvector3d_set_z(_nux_gvector3d_v, value);
            }
        }

        internal IntPtr _nux_gvector3d_v;
    }
}
