// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class PushButton : Widget
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void TriggerEventHandler(IntPtr push_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_push_button_create(IntPtr parent);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_push_button_destroy(IntPtr push_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_push_button_upcast(IntPtr push_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_push_button_get_text(IntPtr push_button, int* size);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_push_button_set_text(IntPtr push_button, byte[] new_text);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_push_button_set_trigger_event_handler(IntPtr push_button, IntPtr event_handler, IntPtr user_data);

        internal static TriggerEventHandler triggerEventHandlerDelegate;
        internal static GCHandle triggerEventHandlerGCHandle;

        public PushButton(IntPtr parent)
            : base(IntPtr.Zero)
        {
            _nux_push_button_v = nux_push_button_create(parent);
            _nux_widget_v = nux_push_button_upcast(_nux_push_button_v);
            _nux_window_element_v = nux_widget_upcast(_nux_widget_v);

            triggerEventHandlerDelegate = HandleNativeTriggerEvent;
            triggerEventHandlerGCHandle = GCHandle.Alloc(triggerEventHandlerDelegate);
            IntPtr triggerEventHandlerDelegatePointer = Marshal.GetFunctionPointerForDelegate(triggerEventHandlerDelegate);
            nux_push_button_set_trigger_event_handler(_nux_push_button_v, triggerEventHandlerDelegatePointer, IntPtr.Zero);
        }

        ~PushButton()
        {
            nux_push_button_destroy(_nux_push_button_v);
            triggerEventHandlerGCHandle.Free();
        }

        public string Text
        {
            get
            {
                int size;
                IntPtr data;
                unsafe
                {
                    data = nux_push_button_get_text(_nux_push_button_v, &size);
                }
                return Impl.ToSystemString(data, size);
            }
            set
            {
                nux_push_button_set_text(_nux_push_button_v, Impl.ToNuxString(value));
            }
        }

        public Action OnTrigger { get; set; }

        private void HandleNativeTriggerEvent(IntPtr push_button)
        {
            OnTrigger?.Invoke();
        }

        internal IntPtr _nux_push_button_v;
    }
}
