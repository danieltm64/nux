// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace Nux
{
    public class Paint
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_paint_destroy(IntPtr paint);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_paint_build_solid_color(IntPtr color, float global_opacity);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_paint_build_linear_gradient(IntPtr start, IntPtr end, IntPtr* stops, int stop_count, float global_opacity);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_paint_build_radial_gradient(IntPtr center, float radius, IntPtr* stops, int stop_count, float global_opacity);

        private Paint(IntPtr handle)
        {
            _nux_paint_v = handle;
        }

        ~Paint()
        {
            nux_paint_destroy(_nux_paint_v);
        }

        public static Paint BuildSolidColor(GVector4D color, float globalOpacity = 1)
        {
            return new Paint(nux_paint_build_solid_color(color._nux_gvector4d_v, globalOpacity));
        }

        public static Paint BuildLinearGradient(GVector2D start, GVector2D end, List<GradientStop> stops, float globalOpacity = 1)
        {
            IntPtr[] stopsArray = new IntPtr[stops.Count];
            for (int i = 0; i < stops.Count; ++i)
            {
                stopsArray[i] = stops[i]._nux_gradient_stop_v;
            }
            unsafe
            {
                fixed (IntPtr* data = stopsArray)
                {
                    return new Paint(nux_paint_build_linear_gradient(start._nux_gvector2d_v, end._nux_gvector2d_v, data, stops.Count, globalOpacity));
                }
            }
        }

        public static Paint BuildRadialGradient(GVector2D center, float radius, List<GradientStop> stops, float globalOpacity = 1)
        {
            IntPtr[] stopsArray = new IntPtr[stops.Count];
            for (int i = 0; i < stops.Count; ++i)
            {
                stopsArray[i] = stops[i]._nux_gradient_stop_v;
            }
            unsafe
            {
                fixed (IntPtr* data = stopsArray)
                {
                    return new Paint(nux_paint_build_radial_gradient(center._nux_gvector2d_v, radius, data, stops.Count, globalOpacity));
                }
            }
        }

        internal IntPtr _nux_paint_v;
    }
}
