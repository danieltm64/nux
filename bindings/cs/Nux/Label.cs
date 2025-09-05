// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class Label : Widget
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void TriggerEventHandler(IntPtr label);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_label_create(IntPtr parent);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_label_destroy(IntPtr label);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_label_upcast(IntPtr label);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_label_get_text(IntPtr label, int* size);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_label_set_text(IntPtr label, byte[] new_text);

        public Label(IntPtr parent)
            : base(IntPtr.Zero)
        {
            _nux_label_v = nux_label_create(parent);
            _nux_widget_v = nux_label_upcast(_nux_label_v);
            _nux_window_element_v = nux_widget_upcast(_nux_widget_v);
        }

        ~Label()
        {
            nux_label_destroy(_nux_label_v);
        }

        public string Text
        {
            get
            {
                int size;
                IntPtr data;
                unsafe
                {
                    data = nux_label_get_text(_nux_label_v, &size);
                }
                return Impl.ToSystemString(data, size);
            }
            set
            {
                nux_label_set_text(_nux_label_v, Impl.ToNuxString(value));
            }
        }

        internal IntPtr _nux_label_v;
    }
}
