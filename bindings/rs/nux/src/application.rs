// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use crate::bindings::*;

pub enum Encoding {
    Utf8,
    Utf16
}

fn map_encoding_t (
    encoding: nux_encoding_t
) -> Encoding {
    return match encoding {
        nux_encoding_t_NUXC_ENCODING_UTF8 => Encoding::Utf8,
        nux_encoding_t_NUXC_ENCODING_UTF16 => Encoding::Utf16,
        _ => unreachable!()
    };
}

fn map_encoding (
    encoding: Encoding
) -> nux_encoding_t {
    return match encoding {
        Encoding::Utf8 => nux_encoding_t_NUXC_ENCODING_UTF8,
        Encoding::Utf16 => nux_encoding_t_NUXC_ENCODING_UTF16,
        _ => unreachable!()
    };
}

impl std::fmt::Display for Encoding {
    fn fmt (
        &self,
        f: &mut std::fmt::Formatter
    ) -> std::fmt::Result {
        return match self {
            Encoding::Utf8 =>  write!(f, "UTF-8"),
            Encoding::Utf16 => write!(f, "UTF-16")
        }
    }
}

pub struct Application {
    handle: *mut nux_application_t
}

impl Application {
    pub fn new (
        args: Vec<String>
    ) -> Self {
        let mut buffers: Vec<Vec<u8>> = args
            .iter()
            .map(|arg| {
                let mut buffer = arg.clone().into_bytes();
                buffer.push(0);
                buffer
            })
            .collect();

        let mut pointers: Vec<*mut c_char> = buffers
            .iter_mut()
            .map(|buffer| buffer.as_mut_ptr() as *mut c_char)
            .collect();

        return Application {
            handle: unsafe {
                nux_application_create(pointers.len() as c_int, pointers.as_mut_ptr())
            }
        };
    }

    pub fn get_encoding () -> Encoding {
        return map_encoding_t(unsafe { nux_application_get_encoding() });
    }

    pub fn run (
        &mut self
    ) -> i32 {
        return unsafe { nux_application_run(self.handle) };
    }
}

impl Drop for Application {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_application_destroy(self.handle)
        };
    }
}