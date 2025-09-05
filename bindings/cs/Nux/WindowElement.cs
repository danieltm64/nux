// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public abstract class WindowElement
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern int nux_window_element_get_x(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_element_set_x(IntPtr window_element, int new_x);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern int nux_window_element_get_y(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_element_set_y(IntPtr window_element, int new_y);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern int nux_window_element_get_width(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_element_set_width(IntPtr window_element, int new_width);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern int nux_window_element_get_height(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_element_set_height(IntPtr window_element, int new_height);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern int nux_window_element_get_horizontal_overhead(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern int nux_window_element_get_vertical_overhead(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern bool nux_window_element_is_dynamically_sized(IntPtr window_element);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_element_set_dynamically_sized(IntPtr window_element, bool new_value);

        protected WindowElement(IntPtr handle)
        {
            _nux_window_element_v = handle;
        }

        public int X
        {
            get
            {
                return nux_window_element_get_x(_nux_window_element_v);
            }
            set
            {
                nux_window_element_set_x(_nux_window_element_v, value);
            }
        }

        public int Y
        {
            get
            {
                return nux_window_element_get_y(_nux_window_element_v);
            }
            set
            {
                nux_window_element_set_y(_nux_window_element_v, value);
            }
        }

        public int Width
        {
            get
            {
                return nux_window_element_get_width(_nux_window_element_v);
            }
            set
            {
                nux_window_element_set_width(_nux_window_element_v, value);
            }
        }

        public int Height
        {
            get
            {
                return nux_window_element_get_height(_nux_window_element_v);
            }
            set
            {
                nux_window_element_set_height(_nux_window_element_v, value);
            }
        }

        public int HorizontalOverhead
        {
            get
            {
                return nux_window_element_get_horizontal_overhead(_nux_window_element_v);
            }
        }

        public int VerticalOverhead
        {
            get
            {
                return nux_window_element_get_vertical_overhead(_nux_window_element_v);
            }
        }

        public bool IsDynamicallySized
        {
            get
            {
                return nux_window_element_is_dynamically_sized(_nux_window_element_v);
            }
            set
            {
                nux_window_element_set_dynamically_sized(_nux_window_element_v, value);
            }
        }

        public abstract void Show();

        public abstract void Hide();

        internal IntPtr _nux_window_element_v;
    }
}
