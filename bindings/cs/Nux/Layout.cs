// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Nux
{
    public enum LayoutKind
    {
        Fixed,
        Flow
    }

    public enum LayoutAxis
    {
        Horizontal,
        Vertical
    }

    public enum LayoutDirection
    {
        Forward,
        Reverse
    }

    public class Layout : WindowElement
    {
        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_layout_create(IntPtr parent, LayoutKind initial_kind, LayoutAxis initial_axis, LayoutDirection initial_direction);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_layout_upcast(IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_layout_grab_parent (IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern LayoutKind nux_layout_get_kind (IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_set_kind (IntPtr layout, LayoutKind new_kind);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern LayoutAxis nux_layout_get_axis (IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_set_axis (IntPtr layout, LayoutAxis new_axis);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern LayoutDirection nux_layout_get_direction (IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_set_direction (IntPtr layout, LayoutDirection new_direction);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_show(IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_hide(IntPtr layout);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_add_widget(IntPtr layout, IntPtr child);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_layout_add_layout(IntPtr layout, IntPtr child);

        internal Layout(IntPtr handle)
            : base(nux_layout_upcast(handle))
        {
            _nux_layout_v = handle;
            _children = new List<WindowElement>();
        }

        public Layout(Layout parent, LayoutKind initialKind, LayoutAxis initialAxis, LayoutDirection initialDirection)
            : base(IntPtr.Zero)
        {
            _nux_layout_v = nux_layout_create(parent == null ? IntPtr.Zero : parent._nux_layout_v, initialKind, initialAxis, initialDirection);
            _nux_window_element_v = nux_layout_upcast(_nux_layout_v);
            _children = new List<WindowElement>();
        }

        public Layout Parent
        {
            get
            {
                return new Layout(nux_layout_grab_parent(_nux_layout_v));
            }
        }

        public LayoutKind Kind
        {
            get
            {
                return nux_layout_get_kind(_nux_layout_v);
            }
            set
            {
                nux_layout_set_kind(_nux_layout_v, value);
            }
        }

        public LayoutAxis Axis
        {
            get
            {
                return nux_layout_get_axis(_nux_layout_v);
            }
            set
            {
                nux_layout_set_axis(_nux_layout_v, value);
            }
        }

        public LayoutDirection Direction
        {
            get
            {
                return nux_layout_get_direction(_nux_layout_v);
            }
            set
            {
                nux_layout_set_direction(_nux_layout_v, value);
            }
        }

        public override void Show()
        {
            nux_layout_show(_nux_layout_v);
        }

        public override void Hide()
        {
            nux_layout_hide(_nux_layout_v);
        }

        public Layout AddLayout(LayoutKind initialKind, LayoutAxis initialAxis, LayoutDirection initialDirection)
        {
            Layout child = new Layout(this, initialKind, initialAxis, initialDirection);
            _children.Add(child);
            nux_layout_add_layout(_nux_layout_v, child._nux_layout_v);
            return child;
        }

        public TWidget AddWidget<TWidget>() where TWidget : Widget
        {
            TWidget child = (TWidget)Activator.CreateInstance(typeof(TWidget), _nux_window_element_v);
            _children.Add(child);
            nux_layout_add_widget(_nux_layout_v, child._nux_widget_v);
            return child;
        }

        public void AddReadyWidget(Widget readyWidget)
        {
            _children.Add(readyWidget);
            nux_layout_add_widget(_nux_layout_v, readyWidget._nux_widget_v);
        }

        internal IntPtr _nux_layout_v;
        internal List<WindowElement> _children;
    }
}
