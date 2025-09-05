// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class RadioButton : Widget
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void ToggleEventHandler(IntPtr radio_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_radio_button_create(IntPtr parent, IntPtr group);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_radio_button_destroy(IntPtr radio_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_radio_button_upcast(IntPtr radio_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_radio_button_get_text(IntPtr radio_button, int* size);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_radio_button_set_text(IntPtr radio_button, byte[] new_text);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern bool nux_radio_button_is_checked(IntPtr radio_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_radio_button_set_checked(IntPtr radio_button, bool new_checked);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_radio_button_set_toggle_event_handler(IntPtr radio_button, IntPtr event_handler, IntPtr user_data);

        internal static ToggleEventHandler toggleEventHandlerDelegate;
        internal static GCHandle toggleEventHandlerGCHandle;

        public RadioButton(IntPtr parent, CheckGroup group)
            : base(IntPtr.Zero)
        {
            _nux_radio_button_v = nux_radio_button_create(parent, group._nux_check_group_v);
            _nux_widget_v = nux_radio_button_upcast(_nux_radio_button_v);
            _nux_window_element_v = nux_widget_upcast(_nux_widget_v);

            toggleEventHandlerDelegate = HandleNativeToggleEvent;
            toggleEventHandlerGCHandle = GCHandle.Alloc(toggleEventHandlerDelegate);
            IntPtr toggleEventHandlerDelegatePointer = Marshal.GetFunctionPointerForDelegate(toggleEventHandlerDelegate);
            nux_radio_button_set_toggle_event_handler(_nux_radio_button_v, toggleEventHandlerDelegatePointer, IntPtr.Zero);
        }

        ~RadioButton()
        {
            nux_radio_button_destroy(_nux_radio_button_v);
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
                    data = nux_radio_button_get_text(_nux_radio_button_v, &size);
                }
                return Impl.ToSystemString(data, size);
            }
            set
            {
                nux_radio_button_set_text(_nux_radio_button_v, Impl.ToNuxString(value));
            }
        }

        public bool Checked
        {
            get
            {
                return nux_radio_button_is_checked(_nux_radio_button_v);
            }
            set
            {
                nux_radio_button_set_checked(_nux_radio_button_v, value);
            }
        }

        public Action OnToggle { get; set; }

        private void HandleNativeToggleEvent(IntPtr radio_button)
        {
            OnToggle?.Invoke();
        }

        internal IntPtr _nux_radio_button_v;
    }

    namespace Extensions
    {
        public static class RadioButtonExtensions
        {
            public static RadioButton AddWidget<TWidget>(this Layout enclosingLayout, CheckGroup group) where TWidget : RadioButton
            {
                RadioButton child = new RadioButton(enclosingLayout._nux_layout_v, group);
                enclosingLayout.AddReadyWidget(child);
                return child;
            }

            public static RadioButton AddWidget<TWidget>(this GroupBox enclosingGroupBox, CheckGroup group) where TWidget : RadioButton
            {
                RadioButton child = new RadioButton(enclosingGroupBox._nux_window_element_v, group);
                enclosingGroupBox.ContentLayout.AddReadyWidget(child);
                return child;
            }
        }
    }
}
