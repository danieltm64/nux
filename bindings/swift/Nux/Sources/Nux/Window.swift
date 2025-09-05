// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public enum WindowMode: Int32 {
    case Standard
    case Maximized
    case Minimized
}

private class WindowCloseEventPayload {
    public let sender: UnsafeMutableRawPointer
    init (
        sender: UnsafeMutableRawPointer
    ) {
        self.sender = sender
    }
}

private func handleNativeCloseEvent (
    nativeSender: OpaquePointer?,
    nativeCloseEvent: OpaquePointer?,
    userData: UnsafeMutableRawPointer?
) {
    if let userData = userData {
        let payload = Unmanaged<WindowCloseEventPayload>.fromOpaque(
            userData
        ).takeUnretainedValue()
        let sender = Unmanaged<Window>.fromOpaque(
            payload.sender
        ).takeUnretainedValue()
        var closeEvent = CloseEvent(handle: nativeCloseEvent)
        sender.handleCloseEvent(closeEvent: closeEvent)
    }
}

open class Window {
    public init (
        title: String,
        width: Int,
        height: Int,
        mode: WindowMode
    ) {
        title.withCString { ctitle in
            self.handle = nux_window_create(
                ctitle,
                Int32(width),
                Int32(height),
                nux_window_mode_t(mode.rawValue)
            )
        }
        self._rootLayout = Layout(
            handle: nux_window_grab_root_layout(self.handle)
        )
        let payload = WindowCloseEventPayload(
            sender: Unmanaged.passRetained(self).toOpaque()
        )
        let userData = Unmanaged.passRetained(payload).toOpaque()

        nux_window_set_close_event_handler(
            self.handle,
            handleNativeCloseEvent,
            userData
        )
    }

    public var rootLayout: Layout {
        get {
            return self._rootLayout!
        }
    }

    public var width: Int {
        get {
            var currentWidth: Int32 = 0
            nux_window_get_size(self.handle, &currentWidth, nil)
            return Int(currentWidth)
        }
        set {
            var currentHeight: Int32 = 0
            nux_window_get_size(self.handle, nil, &currentHeight)
            nux_window_set_size(self.handle, Int32(newValue), currentHeight)
        }
    }

    public var height: Int {
        get {
            var currentHeight: Int32 = 0
            nux_window_get_size(self.handle, nil, &currentHeight)
            return Int(currentHeight)
        }
        set {
            var currentWidth: Int32 = 0
            nux_window_get_size(self.handle, &currentWidth, nil)
            nux_window_set_size(self.handle, currentWidth, Int32(newValue))
        }
    }

    public var title: String {
        get {
            var size: Int32 = 0
            let cresult = nux_window_get_title(self.handle, &size)
            let result = String(
                decoding: UnsafeBufferPointer(start: cresult, count: Int(size)),
                as: UTF8.self
            )
            return result
        }
        set {
            newValue.withCString { ctitle in
                nux_window_set_title(self.handle, ctitle)
            }
        }
    }

    open func handleCloseEvent (
        closeEvent: CloseEvent
    ) {
    }

    public func show () -> Void {
        nux_window_show(self.handle);
    }

    public func hide () -> Void {
        nux_window_hide(self.handle);
    }

    public func center () -> Void {
        nux_window_center(self.handle);
    }

    internal var handle: OpaquePointer? = nil

    private var _rootLayout: Layout? = nil;
}
