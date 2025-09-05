// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;

#[derive(Clone)]
pub struct GVector2D {
    pub(crate) native_handle: *mut nux_gvector2d_t
}

impl GVector2D {
    pub fn new (
        x: f32,
        y: f32
    ) -> Self {
        return Self {
            native_handle: unsafe {
                nux_gvector2d_create(x, y)
            }
        };
    }

    pub fn get_x (
        &self
    ) -> f32 {
        return unsafe {
            nux_gvector2d_get_x(self.native_handle)
        };
    }

    pub fn set_x (
        &self,
        x: f32
    ) {
        unsafe {
            nux_gvector2d_set_x(self.native_handle, x);
        };
    }

    pub fn get_y (
        &self
    ) -> f32 {
        return unsafe {
            nux_gvector2d_get_y(self.native_handle)
        };
    }

    pub fn set_y (
        &self,
        y: f32
    ) {
        unsafe {
            nux_gvector2d_set_y(self.native_handle, y);
        };
    }
}

impl Drop for GVector2D {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_gvector2d_destroy(self.native_handle)
        };
    }
}
