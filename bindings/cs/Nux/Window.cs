// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public enum WindowMode
    {
        Standard,
        Maximized,
        Minimized
    }

    public class Window
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void CloseEventHandler(IntPtr window, IntPtr ev);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_window_create(byte[] initial_title, int initial_width, int initial_height, WindowMode mode);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_destroy(IntPtr window);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_window_grab_root_layout(IntPtr window);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe void nux_window_get_size(IntPtr window, int* width, int* height);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_set_size(IntPtr window, int width, int height);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern unsafe IntPtr nux_window_get_title(IntPtr window, int* size);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_set_title(IntPtr window, byte[] title);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_show(IntPtr window);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_hide(IntPtr window);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_center(IntPtr window);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_window_set_close_event_handler (IntPtr window, IntPtr event_handler, IntPtr user_data);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_close_event_set_should_close (IntPtr close_event, bool new_value);

        internal static CloseEventHandler closeEventHandlerDelegate;
        internal static GCHandle closeEventHandlerGCHandle;

        public Window(string initialTitle, int initialWidth, int initialHeight, WindowMode mode)
        {
            _nux_window_v = nux_window_create(Impl.ToNuxString(initialTitle), initialWidth, initialHeight, mode);

            closeEventHandlerDelegate = HandleNativeCloseEvent;
            closeEventHandlerGCHandle = GCHandle.Alloc(closeEventHandlerDelegate);
            IntPtr closeEventHandlerDelegatePointer = Marshal.GetFunctionPointerForDelegate(closeEventHandlerDelegate);
            nux_window_set_close_event_handler(_nux_window_v, closeEventHandlerDelegatePointer, IntPtr.Zero);
        }

        ~Window()
        {
            nux_window_destroy(_nux_window_v);
            closeEventHandlerGCHandle.Free();
        }

        public Layout RootLayout
        {
            get
            {
                return new Layout(nux_window_grab_root_layout(_nux_window_v));
            }
        }

        public int Width
        {
            get
            {
                int width;
                int height;
                unsafe
                {
                    nux_window_get_size(_nux_window_v, &width, &height);
                }
                return width;
            }
            set
            {
                int height;
                unsafe
                {
                    nux_window_get_size(_nux_window_v, null, &height);
                }
                nux_window_set_size(_nux_window_v, value, height);
            }
        }

        public int Height
        {
            get
            {
                int width;
                int height;
                unsafe
                {
                    nux_window_get_size(_nux_window_v, &width, &height);
                }
                return height;
            }
            set
            {
                int width;
                unsafe
                {
                    nux_window_get_size(_nux_window_v, &width, null);
                }
                nux_window_set_size(_nux_window_v, width, value);
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
                    data = nux_window_get_title(_nux_window_v, &size);
                }
                return Impl.ToSystemString(data, size);
            }
            set
            {
                nux_window_set_title(_nux_window_v, Impl.ToNuxString(value));
            }
        }

        public void Show()
        {
            nux_window_show(_nux_window_v);
        }

        public void Hide()
        {
            nux_window_hide(_nux_window_v);
        }

        public void Center()
        {
            nux_window_center(_nux_window_v);
        }

        private void HandleNativeCloseEvent(IntPtr window, IntPtr ev)
        {
            CloseEvent closeEvent = new CloseEvent(true);
            this.HandleCloseEvent(closeEvent);
            nux_close_event_set_should_close(ev, closeEvent.ShouldClose);
        }

        public virtual void HandleCloseEvent(CloseEvent e)
        {
        }

        private IntPtr _nux_window_v;
    }
}
