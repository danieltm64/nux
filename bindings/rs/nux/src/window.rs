// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::ffi::*;
use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::close_event::*;
use crate::layout::*;

pub enum WindowMode {
    Standard,
    Maximized,
    Minimized
}

fn map_window_mode_t (
    mode: nux_window_mode_t
) -> WindowMode {
    return match mode {
        nux_window_mode_t_NUXC_WINDOW_MODE_STANDARD => WindowMode::Standard,
        nux_window_mode_t_NUXC_WINDOW_MODE_MAXIMIZED => WindowMode::Maximized,
        nux_window_mode_t_NUXC_WINDOW_MODE_MINIMIZED => WindowMode::Minimized,
        _ => unreachable!()
    };
}

fn map_window_mode (
    mode: WindowMode
) -> nux_window_mode_t {
    return match mode {
        WindowMode::Standard => nux_window_mode_t_NUXC_WINDOW_MODE_STANDARD,
        WindowMode::Maximized => nux_window_mode_t_NUXC_WINDOW_MODE_MAXIMIZED,
        WindowMode::Minimized => nux_window_mode_t_NUXC_WINDOW_MODE_MINIMIZED,
        _ => unreachable!()
    };
}

struct WindowHandle {
    native_handle: *mut nux_window_t,
    close_event_handler: Option<Rc<dyn Fn(&mut Window, &mut CloseEvent)>>
}

#[derive(Clone)]
pub struct Window {
    handle_ref: Rc<RefCell<WindowHandle>>
}

impl Window {
    extern "C" fn handle_native_close_event (
        window: *mut nux_window_t,
        close_event: *mut nux_close_event_t,
        user_data: *mut c_void,
    ) {
        let mut window_object = Window::from_window_handle_ref(
            unsafe {
                Rc::from_raw(user_data as *const RefCell<WindowHandle>)
            }
        );
        let mut local_close_event: CloseEvent = CloseEvent::new(true);
        if let Some(ref event_handler) = window_object.handle_ref.clone().borrow().close_event_handler {
            event_handler(&mut window_object, &mut local_close_event);
        }
        /*
        if window_object.handle_ref.borrow().close_event_handler.is_some() {
            let event_handler
                = window_object.handle_ref.borrow().close_event_handler.unwrap();
            event_handler(
                &mut window_object,
                &mut local_close_event
            );
        }
        */
        unsafe {
            nux_close_event_set_should_close(
                close_event,
                local_close_event.should_close()
            );
            nux_window_set_close_event_handler(
                window_object.handle_ref.borrow().native_handle,
                Some(Window::handle_native_close_event),
                Rc::into_raw(window_object.handle_ref.clone()) as *mut c_void
            );
        };
    }

    pub(crate) fn from_window_handle_ref (
        window_handle_ref: Rc<RefCell<WindowHandle>>
    ) -> Self {
        return Window {
            handle_ref: window_handle_ref
        };
    }

    pub fn new (
        title: &str,
        width: i32,
        height: i32,
        mode: WindowMode
    ) -> Self {
        let native_handle = unsafe {
            nux_window_create(
                CString::new(title).unwrap().as_ptr() as *const u8,
                width,
                height,
                map_window_mode(mode)
            )
        };
        let window_handle_ref: Rc<RefCell<WindowHandle>> = Rc::new(
            RefCell::new(
                WindowHandle {
                    native_handle: native_handle,
                    close_event_handler: None
                }
            )
        );
        unsafe {
            nux_window_set_close_event_handler(
                native_handle,
                Some(Window::handle_native_close_event),
                Rc::into_raw(window_handle_ref.clone()) as *mut c_void
            );
        };
        return Window {
            handle_ref: window_handle_ref
        };
    }

    pub fn grab_root_layout (
        &mut self
    ) -> Layout {
        return Layout::from_raw(
            unsafe {
                nux_window_grab_root_layout(
                    self.handle_ref.borrow().native_handle
                ) as *mut nux_layout_t
            }
        );
    }

    pub fn get_size (
        &self,
        width: &mut i32,
        height: &mut i32
    ) {
        unsafe {
            nux_window_get_size(
                self.handle_ref.borrow().native_handle,
                width as *mut i32,
                height as *mut i32
            )
        };
    }

    pub fn set_size (
        &mut self,
        width: i32,
        height: i32
    ) {
        unsafe {
            nux_window_set_size(self.handle_ref.borrow().native_handle, width, height)
        };
    }

    pub fn get_title (
        &self
    ) -> String {
        unsafe {
            let mut size: std::os::raw::c_int = 0;
            let data: *const nuxchar_t = nux_window_get_title(
                self.handle_ref.borrow().native_handle,
                &mut size as *mut std::os::raw::c_int
            );
            return str::from_utf8(
                std::slice::from_raw_parts(
                    data as *const u8,
                    size as usize
                )
            ).unwrap().to_string();
        }
    }

    pub fn set_title (
        &mut self,
        title: &str
    ) {
        unsafe {
            nux_window_set_title(
                self.handle_ref.borrow().native_handle,
                CString::new(title).unwrap().as_ptr() as *const u8
            )
        };
    }

    pub fn show (
        &mut self
    ) {
        unsafe {
            nux_window_show(self.handle_ref.borrow().native_handle)
        };
    }

    pub fn hide (
        &mut self
    ) {
        unsafe {
            nux_window_hide(self.handle_ref.borrow().native_handle)
        };
    }

    pub fn center (
        &mut self
    ) {
        unsafe {
            nux_window_center(self.handle_ref.borrow().native_handle)
        };
    }

    pub fn on_close<T> (
        &mut self,
        close_event_handler: T
    )
    where
        T: Fn (
            &mut Window,
            &mut CloseEvent
        ) + Clone + 'static
    {
        self.handle_ref.borrow_mut().close_event_handler = Some(Rc::new(close_event_handler));
    }
}

impl Drop for WindowHandle {
    fn drop (
        &mut self
    ) {
        unsafe {
            nux_window_destroy(self.native_handle)
        };
    }
}
