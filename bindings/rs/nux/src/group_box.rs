// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::window_element::*;
use crate::layout::*;
use crate::widget::*;

#[derive(Clone)]
pub struct GroupBox {
    widget_handle_ref: WidgetHandleReference
}

impl GroupBox {
    pub fn grab_content_layout (
        &self
    ) -> Layout {
        return Layout::from_raw(
            unsafe {
                nux_group_box_grab_content_layout(
                    self.widget_handle_ref.borrow().handle.native_handle
                        as *mut nux_group_box_t
                ) as *mut nux_layout_t
            }
        );
    }

    pub fn get_title (
        &self
    ) -> String {
        unsafe {
            let mut size: std::os::raw::c_int = 0;
            let data: *const nuxchar_t = nux_group_box_get_title(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_group_box_t,
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

    pub fn set_title (
        &self,
        title: &str
    ) {
        unsafe {
            nux_group_box_set_title(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_group_box_t,
                CString::new(title).unwrap().as_ptr()
                    as *const u8
            );
        };
    }

    pub fn add_widget<T> (
        &self
    ) -> T
    where T: SimpleWidget
    {
        unsafe {
            let widget = T::new(&self.widget_handle_ref.borrow().handle);
            nux_group_box_add_widget(
                self.widget_handle_ref.borrow().handle.native_handle
                    as *mut nux_group_box_t,
                widget.grab_widget_handle().borrow().handle.native_handle
                    as *mut nux_widget_t
            );
            return widget;
        };
    }
}

impl WindowElement for GroupBox {
    fn grab_handle (
        &self
    ) -> WindowElementHandle {
        return self.grab_widget_handle().borrow().handle;
    }
}

impl Widget for GroupBox {
    fn grab_widget_handle (
        &self
    ) -> WidgetHandleReference {
        return self.widget_handle_ref.clone();
    }
}

impl SimpleWidget for GroupBox {
    fn new (
        parent: &WindowElementHandle
    ) -> Self {
        return Self {
            widget_handle_ref: Rc::new(
                RefCell::new(
                    WidgetHandle {
                        handle: WindowElementHandle {
                            native_handle: unsafe {
                                nux_group_box_create(
                                    parent.native_handle
                                ) as *mut nux_window_element_t
                            }
                        },
                        kind: NativeWidgetKind::GroupBox,
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