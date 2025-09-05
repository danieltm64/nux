// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class GradientStop {
    public init (
        position: Float,
        color: GVector4D
    ) {
        self.handle = nux_gradient_stop_create(position, color.handle)
    }

    deinit {
        nux_gradient_stop_destroy(self.handle)
    }

    public var handle: OpaquePointer? = nil
}
