// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class GroupBox : Widget
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void TriggerEventHandler(IntPtr group_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_group_box_create(IntPtr parent);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_group_box_destroy(IntPtr group_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_group_box_upcast(IntPtr group_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_group_box_grab_content_layout(IntPtr group_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_group_box_get_title(IntPtr group_box, int* size);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_group_box_set_title(IntPtr group_box, byte[] new_title);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_group_box_add_widget(IntPtr group_box, IntPtr child);

        public GroupBox(IntPtr parent)
            : base(IntPtr.Zero)
        {
            _nux_group_box_v = nux_group_box_create(parent);
            _nux_widget_v = nux_group_box_upcast(_nux_group_box_v);
            _nux_window_element_v = nux_widget_upcast(_nux_widget_v);
            _contentLayout = new Layout(nux_group_box_grab_content_layout(_nux_group_box_v));
        }

        ~GroupBox()
        {
            nux_group_box_destroy(_nux_group_box_v);
        }

        public Layout ContentLayout
        {
            get
            {
                return _contentLayout;
            }
        }

        public string Title
        {
            get
            {
                int size;
                IntPtr data;
                unsafe
                {
                    data = nux_group_box_get_title(_nux_group_box_v, &size);
                }
                return Impl.ToSystemString(data, size);
            }
            set
            {
                nux_group_box_set_title(_nux_group_box_v, Impl.ToNuxString(value));
            }
        }

        public TWidget AddWidget<TWidget>() where TWidget : Widget
        {
            TWidget child = (TWidget)Activator.CreateInstance(typeof(TWidget), _nux_group_box_v);
            ContentLayout._children.Add(child);
            nux_group_box_add_widget(_nux_group_box_v, child._nux_widget_v);
            return child;
        }

        internal IntPtr _nux_group_box_v;
        private Layout _contentLayout;
    }
}
