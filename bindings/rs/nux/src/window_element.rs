// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;

#[derive(Copy, Clone)]
pub struct WindowElementHandle {
    pub(crate) native_handle: *mut nux_window_element_t
}

pub trait WindowElement {
    fn grab_handle (
        &self
    ) -> WindowElementHandle;

    fn get_x (
        &self
    ) -> i32 {
        return unsafe {
            nux_window_element_get_x(
                self.grab_handle().native_handle
            )
        };
    }

    fn set_x (
        &self,
        x: i32
    ) {
        unsafe {
            nux_window_element_set_x(
                self.grab_handle().native_handle,
                x
            );
        }
    }

    fn get_y (
        &self
    ) -> i32 {
        return unsafe {
            nux_window_element_get_y(
                self.grab_handle().native_handle
            )
        };
    }

    fn set_y (
        &self,
        y: i32
    ) {
        unsafe {
            nux_window_element_set_y(
                self.grab_handle().native_handle,
                y
            );
        }
    }

    fn get_width (
        &self
    ) -> i32 {
        return unsafe {
            nux_window_element_get_width(
                self.grab_handle().native_handle
            )
        };
    }

    fn set_width (
        &self,
        width: i32
    ) {
        unsafe {
            nux_window_element_set_width(
                self.grab_handle().native_handle,
                width
            );
        }
    }

    fn get_height (
        &self
    ) -> i32 {
        return unsafe {
            nux_window_element_get_height(
                self.grab_handle().native_handle
            )
        };
    }

    fn set_height (
        &self,
        height: i32
    ) {
        unsafe {
            nux_window_element_set_height(
                self.grab_handle().native_handle,
                height
            );
        }
    }

    fn get_horizontal_overhead (
        &self
    ) -> i32 {
        return unsafe {
            nux_window_element_get_horizontal_overhead(
                self.grab_handle().native_handle
            )
        };
    }

    fn get_vertical_overhead (
        &self
    ) -> i32 {
        return unsafe {
            nux_window_element_get_vertical_overhead(
                self.grab_handle().native_handle
            )
        };
    }
}
