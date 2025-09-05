// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class GVector4D {
    public init (
        x: Float,
        y: Float,
        z: Float,
        w: Float
    ) {
        self.handle = nux_gvector4d_create(x, y, z, w)
    }

    deinit {
        nux_gvector4d_destroy(self.handle)
    }

    public var x: Float {
        get {
            return nux_gvector4d_get_x(self.handle)
        }
        set {
            nux_gvector4d_set_x(self.handle, newValue)
        }
    }

    public var y: Float {
        get {
            return nux_gvector4d_get_y(self.handle)
        }
        set {
            nux_gvector4d_set_y(self.handle, newValue)
        }
    }

    public var z: Float {
        get {
            return nux_gvector4d_get_z(self.handle)
        }
        set {
            nux_gvector4d_set_z(self.handle, newValue)
        }
    }

    public var w: Float {
        get {
            return nux_gvector4d_get_w(self.handle)
        }
        set {
            nux_gvector4d_set_w(self.handle, newValue)
        }
    }

    public var handle: OpaquePointer? = nil
}
