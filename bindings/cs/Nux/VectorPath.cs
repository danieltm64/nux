// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class VectorPath
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_vector_path_create();

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_destroy(IntPtr vector_path);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_begin_path(IntPtr vector_path, float x, float y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_line_to(IntPtr vector_path, float x, float y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_quad_to(IntPtr vector_path, float cx, float cy, float x, float y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_cubic_to(IntPtr vector_path, float cx1, float cy1, float cx2, float cy2, float x, float y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_close(IntPtr vector_path);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_vector_path_end_path(IntPtr vector_path);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_vector_path_build_rectangle(float x, float y, float width, float height, float radius);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_vector_path_build_circle(float center_x, float center_y, float radius);

        public VectorPath()
        {
            _nux_vector_path_v = nux_vector_path_create();
        }

        private VectorPath(IntPtr handle)
        {
            _nux_vector_path_v = handle;
        }

        ~VectorPath()
        {
            nux_vector_path_destroy(_nux_vector_path_v);
        }

        public void BeginPath(float x, float y)
        {
            nux_vector_path_begin_path(_nux_vector_path_v, x, y);
        }

        public void LineTo(float x, float y)
        {
            nux_vector_path_line_to(_nux_vector_path_v, x, y);
        }

        public void QuadTo(float cx, float cy, float x, float y)
        {
            nux_vector_path_quad_to(_nux_vector_path_v, cx, cy, x, y);
        }

        public void CubicTo(float cx1, float cy1, float cx2, float cy2, float x, float y)
        {
            nux_vector_path_cubic_to(_nux_vector_path_v, cx1, cy1, cx2, cy2, x, y);
        }

        public void Close()
        {
            nux_vector_path_close(_nux_vector_path_v);
        }

        public void EndPath()
        {
            nux_vector_path_end_path(_nux_vector_path_v);
        }

        public static VectorPath BuildRectangle(float x, float y, float width, float height, float radius)
        {
            return new VectorPath(nux_vector_path_build_rectangle(x, y, width, height, radius));
        }

        public static VectorPath BuildCircle(float centerX, float centerY, float radius)
        {
            return new VectorPath(nux_vector_path_build_circle(centerX, centerY, radius));
        }

        internal IntPtr _nux_vector_path_v;
    }
}
