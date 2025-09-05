// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

using System;
using System.Runtime.InteropServices;

namespace Nux
{
    public class GraphicsBox : Widget
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        internal delegate void RenderEventHandler(IntPtr push_button);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_graphics_box_create(IntPtr parent);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_graphics_box_destroy(IntPtr graphics_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern IntPtr nux_graphics_box_upcast(IntPtr graphics_box);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_graphics_box_clear(IntPtr graphics_box, float red, float green, float blue, float alpha);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_graphics_box_fill_path(IntPtr graphics_box, IntPtr path, IntPtr fill_paint);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_graphics_box_stroke_path(IntPtr graphics_box, IntPtr path, IntPtr stroke_paint);

        [DllImport(Impl.SharedLibraryFilename, CharSet = CharSet.Unicode)]
        internal static extern void nux_graphics_box_set_render_event_handler(IntPtr graphics_box, IntPtr event_handler, IntPtr user_data);

        internal static RenderEventHandler renderEventHandlerDelegate;
        internal static GCHandle renderEventHandlerGCHandle;

        public GraphicsBox(IntPtr parent)
            : base(IntPtr.Zero)
        {
            _nux_graphics_box_v = nux_graphics_box_create(parent);
            _nux_widget_v = nux_graphics_box_upcast(_nux_graphics_box_v);
            _nux_window_element_v = nux_widget_upcast(_nux_widget_v);

            renderEventHandlerDelegate = HandleNativeRenderEvent;
            renderEventHandlerGCHandle = GCHandle.Alloc(renderEventHandlerDelegate);
            IntPtr renderEventHandlerDelegatePointer = Marshal.GetFunctionPointerForDelegate(renderEventHandlerDelegate);
            nux_graphics_box_set_render_event_handler(_nux_graphics_box_v, renderEventHandlerDelegatePointer, IntPtr.Zero);
        }

        ~GraphicsBox()
        {
            nux_graphics_box_destroy(_nux_graphics_box_v);
            renderEventHandlerGCHandle.Free();
        }

        public void Clear(float red, float green, float blue, float alpha)
        {
            nux_graphics_box_clear(_nux_graphics_box_v, red, green, blue, alpha);
        }

        public void FillPath(VectorPath path, Paint fillPaint)
        {
            nux_graphics_box_fill_path(_nux_graphics_box_v, path._nux_vector_path_v, fillPaint._nux_paint_v);
        }

        public void StrokePath(VectorPath path, Paint strokePaint)
        {
            nux_graphics_box_stroke_path(_nux_graphics_box_v, path._nux_vector_path_v, strokePaint._nux_paint_v);
        }

        public Action OnRender { get; set; }

        private void HandleNativeRenderEvent(IntPtr graphics_box)
        {
            OnRender?.Invoke();
        }

        internal IntPtr _nux_graphics_box_v;
    }
}
