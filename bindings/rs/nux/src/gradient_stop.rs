// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;
use crate::gvector4d::*;

pub struct GradientStop {
    native_handle: *mut nux_gradient_stop_t
}

impl GradientStop {
    pub fn new (
        position: f32,
        color: GVector4D
    ) -> Self {
        return Self {
            native_handle: unsafe {
                nux_gradient_stop_create(position, color.native_handle)
            }
        };
    }
}

impl Drop for GradientStop {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_gradient_stop_destroy(self.native_handle)
        };
    }
}
