// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class CheckBox : Widget
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void ToggleEventHandler(IntPtr check_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_check_box_create(IntPtr parent);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_check_box_destroy(IntPtr check_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_check_box_upcast(IntPtr check_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_check_box_get_text(IntPtr check_box, int* size);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_check_box_set_text(IntPtr check_box, byte[] new_text);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern bool nux_check_box_is_checked(IntPtr check_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_check_box_set_checked(IntPtr check_box, bool new_checked);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_check_box_set_toggle_event_handler(IntPtr check_box, IntPtr event_handler, IntPtr user_data);

        internal static ToggleEventHandler toggleEventHandlerDelegate;
        internal static GCHandle toggleEventHandlerGCHandle;

        public CheckBox(IntPtr parent)
            : base(IntPtr.Zero)
        {
            _nux_check_box_v = nux_check_box_create(parent);
            _nux_widget_v = nux_check_box_upcast(_nux_check_box_v);
            _nux_window_element_v = nux_widget_upcast(_nux_widget_v);

            toggleEventHandlerDelegate = HandleNativeToggleEvent;
            toggleEventHandlerGCHandle = GCHandle.Alloc(toggleEventHandlerDelegate);
            IntPtr toggleEventHandlerDelegatePointer = Marshal.GetFunctionPointerForDelegate(toggleEventHandlerDelegate);
            nux_check_box_set_toggle_event_handler(_nux_check_box_v, toggleEventHandlerDelegatePointer, IntPtr.Zero);
        }

        ~CheckBox()
        {
            nux_check_box_destroy(_nux_check_box_v);
            toggleEventHandlerGCHandle.Free();
        }

        public string Text
        {
            get
            {
                int size;
                IntPtr data;
                unsafe
                {
                    data = nux_check_box_get_text(_nux_check_box_v, &size);
                }
                return Impl.ToSystemString(data, size);
            }
            set
            {
                nux_check_box_set_text(_nux_check_box_v, Impl.ToNuxString(value));
            }
        }

        public bool Checked
        {
            get
            {
                return nux_check_box_is_checked(_nux_check_box_v);
            }
            set
            {
                nux_check_box_set_checked(_nux_check_box_v, value);
            }
        }

        public Action OnToggle { get; set; }

        private void HandleNativeToggleEvent(IntPtr check_box)
        {
            OnToggle?.Invoke();
        }

        internal IntPtr _nux_check_box_v;
    }
}
