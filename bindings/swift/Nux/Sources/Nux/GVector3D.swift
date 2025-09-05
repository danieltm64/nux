// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class GVector3D {
    public init (
        x: Float,
        y: Float,
        z: Float
    ) {
        self.handle = nux_gvector3d_create(x, y, z)
    }

    deinit {
        nux_gvector3d_destroy(self.handle)
    }

    public var x: Float {
        get {
            return nux_gvector3d_get_x(self.handle)
        }
        set {
            nux_gvector3d_set_x(self.handle, newValue)
        }
    }

    public var y: Float {
        get {
            return nux_gvector3d_get_y(self.handle)
        }
        set {
            nux_gvector3d_set_y(self.handle, newValue)
        }
    }

    public var z: Float {
        get {
            return nux_gvector3d_get_z(self.handle)
        }
        set {
            nux_gvector3d_set_z(self.handle, newValue)
        }
    }

    public var handle: OpaquePointer? = nil
}
