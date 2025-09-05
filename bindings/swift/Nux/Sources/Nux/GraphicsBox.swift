// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public typealias GraphicsBoxRenderEventHandler = () -> Void

private class GraphicsBoxRenderEventPayload {
    public let sender: UnsafeMutableRawPointer
    init (
        sender: UnsafeMutableRawPointer
    ) {
        self.sender = sender
    }
}

private func handleNativeRenderEvent (
    nativeSender: OpaquePointer?,
    userData: UnsafeMutableRawPointer?
) {
    if let userData = userData {
        let payload = Unmanaged<GraphicsBoxRenderEventPayload>.fromOpaque(
            userData
        ).takeUnretainedValue()
        let sender = Unmanaged<GraphicsBox>.fromOpaque(
            payload.sender
        ).takeUnretainedValue()
        sender.render()
    }
}

public class GraphicsBox: Widget, SimpleWidget {
    public var renderEventHandler: GraphicsBoxRenderEventHandler

    public func render () -> Void {
        self.renderEventHandler()
    }

    public func clear (
        red: Float,
        green: Float,
        blue: Float,
        alpha: Float
    ) -> Void {
        nux_graphics_box_clear(self.handle, red, green, blue, alpha)
    }

    public func fillPath (
        path: VectorPath,
        fillPaint: Paint
    ) -> Void {
        nux_graphics_box_fill_path(self.handle, path.handle, fillPaint.handle)
    }

    public func strokePath (
        path: VectorPath,
        strokePaint: Paint
    ) -> Void {
        nux_graphics_box_stroke_path(self.handle, path.handle, strokePaint.handle)
    }

    public override required init (
        handle: OpaquePointer
    ) {
        let cHandle = nux_graphics_box_create(handle)!
        self.renderEventHandler = {}
        super.init(handle: cHandle)

        let payload = GraphicsBoxRenderEventPayload(
            sender: Unmanaged.passRetained(self).toOpaque()
        )
        let userData = Unmanaged.passRetained(payload).toOpaque()

        nux_graphics_box_set_render_event_handler(
            self.handle,
            handleNativeRenderEvent,
            userData
        )
    }
}
