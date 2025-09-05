// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::window_element::*;
use crate::push_button::*;
use crate::check_box::*;
use crate::radio_button::*;
use crate::graphics_box::*;

#[derive(Copy, Clone)]
pub enum NativeWidgetKind {
    Label,
    PushButton,
    CheckBox,
    RadioButton,
    GroupBox,
    GraphicsBox
}

pub(crate) struct WidgetHandle {
    pub handle: WindowElementHandle,
    pub kind: NativeWidgetKind,
    pub graphics_box_render_event_handler: Option<Rc<dyn Fn()>>,
    pub push_button_trigger_event_handler: Option<Rc<dyn Fn()>>,
    pub check_box_toggle_event_handler: Option<Rc<dyn Fn()>>,
    pub radio_button_toggle_event_handler: Option<Rc<dyn Fn()>>
}

pub(crate) type WidgetHandleReference = Rc<RefCell<WidgetHandle>>;

pub trait Widget: WindowElement {
    fn grab_widget_handle (
        &self
    ) -> WidgetHandleReference;

    fn grab_handle (
        &self
    ) -> WindowElementHandle {
        self.grab_widget_handle().borrow().handle
    }

    fn is_enabled (
        &self
    ) -> bool {
        return unsafe {
            nux_widget_is_enabled(
                self.grab_widget_handle().borrow().handle.native_handle
                    as *mut nux_widget_t
            )
        };
    }

    fn set_enabled (
        &self,
        enabled: bool
    ) {
        unsafe {
            nux_widget_set_enabled(
                self.grab_widget_handle().borrow().handle.native_handle
                    as *mut nux_widget_t,
                enabled
            )
        };
    }
}

pub trait SimpleWidget: Widget {
    fn new (
        parent: &WindowElementHandle
    ) -> Self;
}