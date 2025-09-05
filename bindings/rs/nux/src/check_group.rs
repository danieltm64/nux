// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use crate::bindings::*;

pub struct CheckGroup {
    pub(crate) native_handle: *mut nux_check_group_t
}

impl CheckGroup {
    pub fn new () -> Self {
        return Self {
            native_handle: unsafe {
                nux_check_group_create()
            }
        };
    }
}

impl Drop for CheckGroup {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_check_group_destroy(self.native_handle)
        };
    }
}
