// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::window_element::*;
use crate::widget::*;

#[derive(Clone)]
pub struct PushButton {
    widget_handle_ref: WidgetHandleReference
}

impl PushButton {
    extern "C" fn handle_native_trigger_event (
        handle: *mut nux_push_button_t,
        user_data: *mut c_void
    ) {
        let mut widget_handle_ref = unsafe {
            Rc::from_raw(user_data as *const RefCell<WidgetHandle>)
        };
        if let Some(ref event_handler) = widget_handle_ref.borrow().push_button_trigger_event_handler {
            event_handler();
        }
        unsafe {
            nux_push_button_set_trigger_event_handler(
                widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_push_button_t,
                Some(PushButton::handle_native_trigger_event),
                Rc::into_raw(widget_handle_ref.clone()) as *mut c_void
            );
        }
    }

    pub fn clone (
        &self
    ) -> Self {
        return Self {
            widget_handle_ref: self.widget_handle_ref.clone()
        }
    }

    pub fn get_text (
        &self
    ) -> String {
        unsafe {
            let mut size: std::os::raw::c_int = 0;
            let data: *const nuxchar_t = nux_push_button_get_text(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_push_button_t,
                &mut size as *mut std::os::raw::c_int
            );
            return str::from_utf8(
                std::slice::from_raw_parts(
                    data as *const u8,
                    size as usize
                )
            ).unwrap().to_string();
        }
    }

    pub fn set_text (
        &self,
        text: &str
    ) {
        unsafe {
            nux_push_button_set_text(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_push_button_t,
                CString::new(text).unwrap().as_ptr()
                    as *const u8
            );
        };
    }

    pub fn on_trigger<T> (
        &mut self,
        trigger_event_handler: T
    )
    where
        T: Fn () + Clone + 'static
    {
        self.widget_handle_ref.borrow_mut().push_button_trigger_event_handler = Some(Rc::new(trigger_event_handler));
    }
}

impl WindowElement for PushButton {
    fn grab_handle (
        &self
    ) -> WindowElementHandle {
        return self.grab_widget_handle().borrow().handle;
    }
}

impl Widget for PushButton {
    fn grab_widget_handle (
        &self
    ) -> WidgetHandleReference {
        return self.widget_handle_ref.clone();
    }
}

impl SimpleWidget for PushButton {
    fn new (
        parent: &WindowElementHandle
    ) -> Self {
        let native_handle = unsafe {
            nux_push_button_create(
                parent.native_handle
            ) as *mut nux_window_element_t
        };
        let widget_handle_ref = Rc::new(
            RefCell::new(
                WidgetHandle {
                    handle: WindowElementHandle {
                        native_handle: native_handle
                    },
                    kind: NativeWidgetKind::PushButton,
                    graphics_box_render_event_handler: None,
                    push_button_trigger_event_handler: None,
                    check_box_toggle_event_handler: None,
                    radio_button_toggle_event_handler: None
                }
            )
        );
        unsafe {
            nux_push_button_set_trigger_event_handler(
                native_handle
                    as *mut nux_push_button_t,
                Some(PushButton::handle_native_trigger_event),
                Rc::into_raw(widget_handle_ref.clone()) as *mut c_void
            );
        };
        return Self {
            widget_handle_ref: widget_handle_ref
        };
    }
}
