// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use crate::bindings::*;
use crate::gvector2d::*;
use crate::gvector4d::*;
use crate::gradient_stop::*;

#[derive(Clone)]
pub struct Paint {
    pub(crate) native_handle: *mut nux_paint_t
}

impl Paint {
    pub fn build_solid_color (
        color: GVector4D,
        global_opacity: f32
    ) -> Self {
        return Self {
            native_handle: unsafe {
                nux_paint_build_solid_color(
                    color.native_handle,
                    global_opacity
                )
            }
        };
    }

    pub fn build_linear_gradient (
        start: GVector2D,
        end: GVector2D,
        stops: &Vec<GradientStop>,
        global_opacity: f32
    ) -> Self {
        return Self {
            native_handle: unsafe {
                nux_paint_build_linear_gradient(
                    start.native_handle,
                    end.native_handle,
                    stops.as_ptr() as *mut *mut nux_gradient_stop_t,
                    stops.len() as c_int,
                    global_opacity
                )
            }
        };
    }

    pub fn build_radial_gradient (
        center: GVector2D,
        radius: f32,
        stops: &Vec<GradientStop>,
        global_opacity: f32
    ) -> Self {
        return Self {
            native_handle: unsafe {
                nux_paint_build_radial_gradient(
                    center.native_handle,
                    radius,
                    stops.as_ptr() as *mut *mut nux_gradient_stop_t,
                    stops.len() as c_int,
                    global_opacity
                )
            }
        };
    }
}

impl Drop for Paint {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_paint_destroy(self.native_handle)
        };
    }
}
