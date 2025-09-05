// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class WindowElement {
    public var x: Int {
        get {
            return Int(nux_window_element_get_x(self.handle))
        }
        set {
            nux_window_element_set_x(self.handle, Int32(newValue))
        }
    }

    public var y: Int {
        get {
            return Int(nux_window_element_get_y(self.handle))
        }
        set {
            nux_window_element_set_y(self.handle, Int32(newValue))
        }
    }

    public var width: Int {
        get {
            return Int(nux_window_element_get_width(self.handle))
        }
        set {
            nux_window_element_set_width(self.handle, Int32(newValue))
        }
    }

    public var height: Int {
        get {
            return Int(nux_window_element_get_height(self.handle))
        }
        set {
            nux_window_element_set_height(self.handle, Int32(newValue))
        }
    }

    public var horizontalOverhead: Int {
        get {
            return Int(nux_window_element_get_horizontal_overhead(self.handle))
        }
    }

    public var verticalOverhead: Int {
        get {
            return Int(nux_window_element_get_vertical_overhead(self.handle))
        }
    }

    public var isDynamicallySized: Bool {
        get {
            return nux_window_element_is_dynamically_sized(self.handle)
        }
        set {
            nux_window_element_set_dynamically_sized(self.handle, newValue)
        }
    }

    public var handle: OpaquePointer? = nil

    internal init (
        handle: OpaquePointer
    ) {
        self.handle = handle
    }
}
