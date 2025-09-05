// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class VectorPath {
    public func beginPath (
        x: Float,
        y: Float
    ) {
        nux_vector_path_begin_path(self.handle, x, y);
    }

    public func lineTo (
        x: Float,
        y: Float
    ) {
        nux_vector_path_line_to(self.handle, x, y);
    }

    public func quadTo (
        cx: Float,
        cy: Float,
        x: Float,
        y: Float
    ) {
        nux_vector_path_quad_to(self.handle, cx, cy, x, y);
    }

    public func cubicTo (
        cx1: Float,
        cy1: Float,
        cx2: Float,
        cy2: Float,
        x: Float,
        y: Float
    ) {
        nux_vector_path_cubic_to(self.handle, cx1, cy1, cx2, cy2, x, y);
    }

    public func close () {
        nux_vector_path_close(self.handle)
    }

    public func endPath () {
        nux_vector_path_end_path(self.handle)
    }

    public static func buildRectangle (
        x: Float,
        y: Float,
        width: Float,
        height: Float,
        radius: Float
    ) -> VectorPath {
        return VectorPath(
            handle: nux_vector_path_build_rectangle(
                x,
                y,
                width,
                height,
                radius
            )
        )
    }

    public static func buildCircle (
        centerX: Float,
        centerY: Float,
        radius: Float
    ) -> VectorPath {
        return VectorPath(
            handle: nux_vector_path_build_circle(
                centerX,
                centerY,
                radius
            )
        )
    }

    deinit {
        nux_vector_path_destroy(self.handle)
    }

    public var handle: OpaquePointer? = nil

    public init () {
        self.handle = nux_vector_path_create()!
    }

    private init (
        handle: OpaquePointer
    ) {
        self.handle = handle
    }
}
