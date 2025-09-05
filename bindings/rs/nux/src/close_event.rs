// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;
use crate::event::*;

pub struct CloseEvent {
    native_handle: *mut nux_close_event_t
}

impl CloseEvent {
    pub fn new (
        should_close: bool
    ) -> Self {
        return CloseEvent {
            native_handle: unsafe {
                nux_close_event_create(should_close)
            }
        };
    }

    pub fn should_close (
        &self
    ) -> bool {
        return unsafe { nux_close_event_should_close(self.native_handle) };
    }

    pub fn set_should_close (
        &mut self,
        should_close: bool
    ) {
        unsafe { nux_close_event_set_should_close(self.native_handle, should_close) };
    }
}

impl Drop for CloseEvent {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_close_event_destroy(self.native_handle)
        };
    }
}

impl AccessEventType for CloseEvent {
    fn get_event_type (
        &self
    ) -> EventType {
        return map_event_type_t(
            unsafe { nux_event_get_event_type(self.native_handle as *mut nux_event_t) }
        );
    }
}
