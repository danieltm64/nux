// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;

pub enum EventType {
    KeyEvent,
    CloseEvent
}

pub(crate) fn map_event_type_t (
    event_type: nux_event_type_t
) -> EventType {
    return match event_type {
        nux_event_type_t_NUXC_EVENT_TYPE_KEY_EVENT => EventType::KeyEvent,
        nux_event_type_t_NUXC_EVENT_TYPE_CLOSE_EVENT => EventType::CloseEvent,
        _ => unreachable!()
    };
}

pub(crate) fn map_event_type (
    event_type: EventType
) -> nux_event_type_t {
    return match event_type {
        EventType::KeyEvent => nux_event_type_t_NUXC_EVENT_TYPE_KEY_EVENT,
        EventType::CloseEvent => nux_event_type_t_NUXC_EVENT_TYPE_CLOSE_EVENT,
        _ => unreachable!()
    };
}

pub(crate) trait AccessEventType {
    fn get_event_type (
        &self
    ) -> EventType;
}

pub struct Event {
    native_handle: *mut nux_event_t
}

impl Event {
    pub fn new (
        event_type: EventType
    ) -> Self {
        return Event {
            native_handle: unsafe {
                nux_event_create(map_event_type(event_type))
            }
        };
    }
}

impl Drop for Event {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_event_destroy(self.native_handle)
        };
    }
}

impl AccessEventType for Event {
    fn get_event_type (
        &self
    ) -> EventType {
        return map_event_type_t(
            unsafe { nux_event_get_event_type(self.native_handle) }
        );
    }
}
