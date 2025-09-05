// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;

#[derive(Clone)]
pub struct GVector4D {
    pub(crate) native_handle: *mut nux_gvector4d_t
}

impl GVector4D {
    pub fn new (
        x: f32,
        y: f32,
        z: f32,
        w: f32
    ) -> Self {
        return Self {
            native_handle: unsafe {
                nux_gvector4d_create(x, y, z, w)
            }
        };
    }

    pub fn get_x (
        &self
    ) -> f32 {
        return unsafe {
            nux_gvector4d_get_x(self.native_handle)
        };
    }

    pub fn set_x (
        &self,
        x: f32
    ) {
        unsafe {
            nux_gvector4d_set_x(self.native_handle, x);
        };
    }

    pub fn get_y (
        &self
    ) -> f32 {
        return unsafe {
            nux_gvector4d_get_y(self.native_handle)
        };
    }

    pub fn set_y (
        &self,
        y: f32
    ) {
        unsafe {
            nux_gvector4d_set_y(self.native_handle, y);
        };
    }

    pub fn get_z (
        &self
    ) -> f32 {
        return unsafe {
            nux_gvector4d_get_z(self.native_handle)
        };
    }

    pub fn set_z (
        &self,
        z: f32
    ) {
        unsafe {
            nux_gvector4d_set_z(self.native_handle, z);
        };
    }

    pub fn get_w (
        &self
    ) -> f32 {
        return unsafe {
            nux_gvector4d_get_w(self.native_handle)
        };
    }

    pub fn set_w (
        &self,
        w: f32
    ) {
        unsafe {
            nux_gvector4d_set_w(self.native_handle, w);
        };
    }
}

impl Drop for GVector4D {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_gvector4d_destroy(self.native_handle)
        };
    }
}
