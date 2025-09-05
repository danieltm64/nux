// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class Widget : WindowElement
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_widget_upcast(IntPtr widget);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_widget_grab_native_handle(IntPtr widget);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern bool nux_widget_is_enabled(IntPtr widget);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_widget_set_enabled(IntPtr widget, bool new_enabled);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_widget_show(IntPtr widget);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_widget_hide(IntPtr widget);

        protected Widget(IntPtr handle)
            : base(nux_widget_upcast(handle))
        {
            _nux_widget_v = handle;
        }

        public bool Enabled
        {
            get
            {
                return nux_widget_is_enabled(_nux_widget_v);
            }
            set
            {
                nux_widget_set_enabled(_nux_widget_v, value);
            }
        }

        public override void Show()
        {
            nux_widget_show(_nux_widget_v);
        }

        public override void Hide()
        {
            nux_widget_hide(_nux_widget_v);
        }

        internal IntPtr _nux_widget_v;
    }
}
