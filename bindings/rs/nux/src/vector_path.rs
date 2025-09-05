// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;

#[derive(Clone)]
pub struct VectorPath {
    pub(crate) native_handle: *mut nux_vector_path_t
}

impl VectorPath {
    pub fn new () -> Self {
        return VectorPath {
            native_handle: unsafe {
                nux_vector_path_create()
            }
        };
    }

    pub fn begin_path (
        &mut self,
        x: f32,
        y: f32
    ) {
        unsafe {
            nux_vector_path_begin_path(self.native_handle, x, y)
        };
    }

    pub fn line_to (
        &mut self,
        x: f32,
        y: f32
    ) {
        unsafe {
            nux_vector_path_line_to(self.native_handle, x, y)
        };
    }

    pub fn quad_to (
        &mut self,
        cx:  f32,
        cy:  f32,
        x: f32,
        y: f32
    ) {
        unsafe {
            nux_vector_path_quad_to(self.native_handle, cx, cy, x, y)
        };
    }

    pub fn cubic_to (
        &mut self,
        cx1:  f32,
        cy1:  f32,
        cx2:  f32,
        cy2:  f32,
        x: f32,
        y: f32
    ) {
        unsafe {
            nux_vector_path_cubic_to(
                self.native_handle,
                cx1,
                cy1,
                cx2,
                cy2,
                x,
                y
            )
        };
    }

    pub fn close (
        &mut self
    ) {
        unsafe {
            nux_vector_path_close(self.native_handle)
        };
    }

    pub fn end_path (
        &mut self,
        x: f32,
        y: f32
    ) {
        unsafe {
            nux_vector_path_begin_path(self.native_handle, x, y)
        };
    }

    pub fn build_rectangle (
        x: f32,
        y: f32,
        width: f32,
        height: f32,
        radius: f32
    ) -> Self {
        return VectorPath {
            native_handle: unsafe {
                nux_vector_path_build_rectangle(x, y, width, height, radius)
            }
        };
    }

    pub fn build_circle (
        center_x: f32,
        center_y: f32,
        radius: f32
    ) -> Self {
        return VectorPath {
            native_handle: unsafe {
                nux_vector_path_build_circle(center_x, center_y, radius)
            }
        };
    }
}

impl Drop for VectorPath {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_vector_path_destroy(self.native_handle)
        };
    }
}
