// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::window_element::*;
use crate::widget::*;
use crate::vector_path::*;
use crate::paint::*;

#[derive(Clone)]
pub struct GraphicsBox {
    widget_handle_ref: WidgetHandleReference
}

impl GraphicsBox {
    extern "C" fn handle_native_render_event (
        graphics_box: *mut nux_graphics_box_t,
        user_data: *mut c_void
    ) {
        let mut widget_handle_ref = unsafe {
            Rc::from_raw(user_data as *const RefCell<WidgetHandle>)
        };
        if let Some(ref event_handler) = widget_handle_ref.borrow().graphics_box_render_event_handler {
            event_handler();
        }
        unsafe {
            nux_graphics_box_set_render_event_handler(
                widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_graphics_box_t,
                Some(GraphicsBox::handle_native_render_event),
                Rc::into_raw(widget_handle_ref.clone()) as *mut c_void
            );
        }
    }

    pub fn clear (
        &self,
        red: f32,
        green: f32,
        blue: f32,
        alpha: f32
    ) {
        unsafe {
            nux_graphics_box_clear(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_graphics_box_t,
                red,
                green,
                blue,
                alpha
            );
        }
    }

    pub fn fill_path (
        &self,
        path: &VectorPath,
        fill_paint: &Paint
    ) {
        unsafe {
            nux_graphics_box_fill_path(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_graphics_box_t,
                path.native_handle,
                fill_paint.native_handle
            );
        }
    }

    pub fn stroke_path (
        &self,
        path: &VectorPath,
        stroke_paint: &Paint
    ) {
        unsafe {
            nux_graphics_box_stroke_path(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_graphics_box_t,
                path.native_handle,
                stroke_paint.native_handle
            );
        }
    }

    pub fn on_render<T> (
        &mut self,
        render_event_handler: T
    )
    where
        T: Fn () + Clone + 'static
    {
        self.widget_handle_ref.borrow_mut().graphics_box_render_event_handler = Some(Rc::new(render_event_handler));
    }
}

impl WindowElement for GraphicsBox {
    fn grab_handle (
        &self
    ) -> WindowElementHandle {
        return self.grab_widget_handle().borrow().handle;
    }
}

impl Widget for GraphicsBox {
    fn grab_widget_handle (
        &self
    ) -> WidgetHandleReference {
        return self.widget_handle_ref.clone();
    }
}

impl SimpleWidget for GraphicsBox {
    fn new (
        parent: &WindowElementHandle
    ) -> Self {
        let native_handle = unsafe {
            nux_graphics_box_create(
                parent.native_handle
            ) as *mut nux_window_element_t
        };
        let widget_handle_ref = Rc::new(
            RefCell::new(
                WidgetHandle {
                    handle: WindowElementHandle {
                        native_handle: native_handle
                    },
                    kind: NativeWidgetKind::GraphicsBox,
                    graphics_box_render_event_handler: None,
                    push_button_trigger_event_handler: None,
                    check_box_toggle_event_handler: None,
                    radio_button_toggle_event_handler: None
                }
            )
        );
        unsafe {
            nux_graphics_box_set_render_event_handler(
                native_handle
                    as *mut nux_graphics_box_t,
                Some(GraphicsBox::handle_native_render_event),
                Rc::into_raw(widget_handle_ref.clone()) as *mut c_void
            );
        };
        return Self {
            widget_handle_ref: widget_handle_ref
        };
    }
}