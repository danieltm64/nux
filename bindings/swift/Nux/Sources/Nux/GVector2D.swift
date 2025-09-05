// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class GVector2D {
    public init (
        x: Float,
        y: Float
    ) {
        self.handle = nux_gvector2d_create(x, y)
    }

    deinit {
        nux_gvector2d_destroy(self.handle)
    }

    public var x: Float {
        get {
            return nux_gvector2d_get_x(self.handle)
        }
        set {
            nux_gvector2d_set_x(self.handle, newValue)
        }
    }

    public var y: Float {
        get {
            return nux_gvector2d_get_y(self.handle)
        }
        set {
            nux_gvector2d_set_y(self.handle, newValue)
        }
    }

    public var handle: OpaquePointer? = nil
}
