// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class Paint {
    public static func buildSolidColor (
        color: GVector4D,
        globalOpacity: Float = 1
    ) -> Paint {
        return Paint(
            handle: nux_paint_build_solid_color(
                color.handle,
                globalOpacity
            )
        )
    }

    public static func buildLinearGradient (
        start: GVector2D,
        end: GVector2D,
        stops: [GradientStop],
        globalOpacity: Float = 1
    ) -> Paint {
        var result = Paint(handle: nil)
        var opaquePointers: [OpaquePointer?] = stops.map { $0.handle }
        opaquePointers.withUnsafeMutableBufferPointer { buffer in
            result.handle = nux_paint_build_linear_gradient(
                start.handle,
                end.handle,
                buffer.baseAddress,
                Int32(stops.count),
                globalOpacity
            )
        }
        return result
    }

    public static func buildRadialGradient (
        center: GVector2D,
        radius: Float,
        stops: [GradientStop],
        globalOpacity: Float = 1
    ) -> Paint {
        var result = Paint(handle: nil)
        var opaquePointers: [OpaquePointer?] = stops.map { $0.handle }
        opaquePointers.withUnsafeMutableBufferPointer { buffer in
            result.handle = nux_paint_build_radial_gradient(
                center.handle,
                radius,
                buffer.baseAddress,
                Int32(stops.count),
                globalOpacity
            )
        }
        return result
    }

    deinit {
        nux_paint_destroy(self.handle)
    }

    public var handle: OpaquePointer? = nil

    private init (
        handle: OpaquePointer?
    ) {
        self.handle = handle
    }
}
