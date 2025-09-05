// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

use std::rc::*;
use std::cell::*;
use crate::bindings::*;
use crate::window_element::*;
use crate::widget::*;
use crate::radio_button::*;
use crate::check_group::*;

pub enum LayoutKind {
    Fixed,
    Flow
}

pub enum LayoutAxis {
    Horizontal,
    Vertical
}

pub enum LayoutDirection {
    Forward,
    Reverse
}

fn map_layout_kind (
    kind: LayoutKind
) -> nux_layout_kind_t {
    return match kind {
        LayoutKind::Fixed => nux_layout_kind_t_NUXC_LAYOUT_KIND_FIXED,
        LayoutKind::Flow => nux_layout_kind_t_NUXC_LAYOUT_KIND_FLOW,
        _ => unreachable!()
    };
}

fn map_layout_kind_t (
    kind: nux_layout_kind_t
) -> LayoutKind {
    return match kind {
        nux_layout_kind_t_NUXC_LAYOUT_KIND_FIXED => LayoutKind::Fixed,
        nux_layout_kind_t_NUXC_LAYOUT_KIND_FLOW => LayoutKind::Flow,
        _ => unreachable!()
    };
}

fn map_layout_axis (
    axis: LayoutAxis
) -> nux_layout_axis_t {
    return match axis {
        LayoutAxis::Horizontal => nux_layout_axis_t_NUXC_LAYOUT_AXIS_HORIZONTAL,
        LayoutAxis::Vertical => nux_layout_axis_t_NUXC_LAYOUT_AXIS_VERTICAL,
        _ => unreachable!()
    };
}

fn map_layout_axis_t (
    axis: nux_layout_axis_t
) -> LayoutAxis {
    return match axis {
        nux_layout_axis_t_NUXC_LAYOUT_AXIS_HORIZONTAL => LayoutAxis::Horizontal,
        nux_layout_axis_t_NUXC_LAYOUT_AXIS_VERTICAL => LayoutAxis::Vertical,
        _ => unreachable!()
    };
}

fn map_layout_direction (
    direction: LayoutDirection
) -> nux_layout_direction_t {
    return match direction {
        LayoutDirection::Forward => nux_layout_direction_t_NUXC_LAYOUT_DIRECTION_FORWARD,
        LayoutDirection::Reverse => nux_layout_direction_t_NUXC_LAYOUT_DIRECTION_REVERSE,
        _ => unreachable!()
    };
}

fn map_layout_direction_t (
    direction: nux_layout_direction_t
) -> LayoutDirection {
    return match direction {
        nux_layout_direction_t_NUXC_LAYOUT_DIRECTION_FORWARD => LayoutDirection::Forward,
        nux_layout_direction_t_NUXC_LAYOUT_DIRECTION_REVERSE => LayoutDirection::Reverse,
        _ => unreachable!()
    };
}

pub struct Layout {
    pub(crate) handle: WindowElementHandle
}

impl Layout {
    pub(crate) fn from_raw (
        native_handle: *mut nux_layout_t
    ) -> Self {
        return Self {
            handle: WindowElementHandle {
                native_handle: native_handle as *mut nux_window_element_t
            }
        };
    }

    pub fn new (
        parent: &Layout,
        kind: LayoutKind,
        axis: LayoutAxis,
        direction: LayoutDirection
    ) -> Self {
        return Self {
            handle: WindowElementHandle {
                native_handle: unsafe {
                    nux_layout_create(
                        parent.handle.native_handle as *mut nux_layout_t,
                        map_layout_kind(kind),
                        map_layout_axis(axis),
                        map_layout_direction(direction)
                    ) as *mut nux_window_element_t
                }
            }
        };
    }

    pub fn grab_parent (
        &mut self
    ) -> Self {
        return Self {
            handle: WindowElementHandle {
                native_handle: unsafe {
                    nux_layout_grab_parent(
                        self.handle.native_handle as *mut nux_layout_t
                    ) as *mut nux_window_element_t
                }
            }
        };
    }

    pub fn get_kind (
        &self
    ) -> LayoutKind {
        return unsafe {
            map_layout_kind_t(
                nux_layout_get_kind(
                    self.handle.native_handle as *mut nux_layout_t
                )
            )
        };
    }

    pub fn set_kind (
        &mut self,
        kind: LayoutKind
    ) {
        unsafe {
            nux_layout_set_kind(
                self.handle.native_handle as *mut nux_layout_t,
                map_layout_kind(kind)
            );
        };
    }

    pub fn get_axis (
        &self
    ) -> LayoutAxis {
        return unsafe {
            map_layout_axis_t(
                nux_layout_get_axis(
                    self.handle.native_handle as *mut nux_layout_t
                )
            )
        };
    }

    pub fn set_axis (
        &mut self,
        axis: LayoutAxis
    ) {
        unsafe {
            nux_layout_set_axis(
                self.handle.native_handle as *mut nux_layout_t,
                map_layout_axis(axis)
            );
        };
    }

    pub fn get_direction (
        &self
    ) -> LayoutDirection {
        return unsafe {
            map_layout_direction_t(
                nux_layout_get_direction(
                    self.handle.native_handle as *mut nux_layout_t
                )
            )
        };
    }

    pub fn set_direction (
        &mut self,
        direction: LayoutDirection
    ) {
        unsafe {
            nux_layout_set_direction(
                self.handle.native_handle as *mut nux_layout_t,
                map_layout_direction(direction)
            );
        };
    }

    pub fn show (
        &mut self
    ) {
        unsafe {
            nux_layout_show(self.handle.native_handle as *mut nux_layout_t);
        };
    }

    pub fn add_widget<T> (
        &mut self
    ) -> T
    where T: SimpleWidget
    {
        unsafe {
            let widget = T::new(&self.handle);
            nux_layout_add_widget(
                self.handle.native_handle as *mut nux_layout_t,
                widget.grab_widget_handle().borrow().handle.native_handle
                    as *mut nux_widget_t
            );
            return widget;
        };
    }

    pub fn add_radio_button (
        &mut self,
        group: &CheckGroup
    ) -> RadioButton {
        unsafe {
            let widget = RadioButton::new(&self.handle, group);
            nux_layout_add_widget(
                self.handle.native_handle as *mut nux_layout_t,
                widget.grab_widget_handle().borrow().handle.native_handle
                    as *mut nux_widget_t
            );
            return widget;
        };
    }
}
