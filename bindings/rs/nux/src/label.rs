// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::window_element::*;
use crate::widget::*;

#[derive(Clone)]
pub struct Label {
    widget_handle_ref: WidgetHandleReference
}

impl Label {
    pub fn get_text (
        &self
    ) -> String {
        unsafe {
            let mut size: std::os::raw::c_int = 0;
            let data: *const nuxchar_t = nux_label_get_text(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_label_t,
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
            nux_label_set_text(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_label_t,
                CString::new(text).unwrap().as_ptr()
                    as *const u8
            );
        };
    }
}

impl WindowElement for Label {
    fn grab_handle (
        &self
    ) -> WindowElementHandle {
        return self.grab_widget_handle().borrow().handle;
    }
}

impl Widget for Label {
    fn grab_widget_handle (
        &self
    ) -> WidgetHandleReference {
        return self.widget_handle_ref.clone();
    }
}

impl SimpleWidget for Label {
    fn new (
        parent: &WindowElementHandle
    ) -> Self {
        return Self {
            widget_handle_ref: Rc::new(
                RefCell::new(
                    WidgetHandle {
                        handle: WindowElementHandle {
                            native_handle: unsafe {
                                nux_label_create(
                                    parent.native_handle
                                ) as *mut nux_window_element_t
                            }
                        },
                        kind: NativeWidgetKind::Label,
                        graphics_box_render_event_handler: None,
                        push_button_trigger_event_handler: None,
                        check_box_toggle_event_handler: None,
                        radio_button_toggle_event_handler: None
                    }
                )
            )
        };
    }
}