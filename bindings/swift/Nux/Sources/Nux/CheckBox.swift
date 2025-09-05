// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public typealias CheckBoxToggleEventHandler = () -> Void

private class CheckBoxToggleEventPayload {
    public let sender: UnsafeMutableRawPointer
    init (
        sender: UnsafeMutableRawPointer
    ) {
        self.sender = sender
    }
}

private func handleNativeToggleEvent (
    nativeSender: OpaquePointer?,
    userData: UnsafeMutableRawPointer?
) {
    if let userData = userData {
        let payload = Unmanaged<CheckBoxToggleEventPayload>.fromOpaque(
            userData
        ).takeUnretainedValue()
        let sender = Unmanaged<CheckBox>.fromOpaque(
            payload.sender
        ).takeUnretainedValue()
        sender.toggle()
    }
}

public class CheckBox: Widget, SimpleWidget {
    public var text: String {
        get {
            var size: Int32 = 0
            let cresult = nux_check_box_get_text(self.handle, &size)
            let result = String(
                decoding: UnsafeBufferPointer(
                    start: cresult,
                    count: Int(size)
                ),
                as: UTF8.self
            )
            return result
        }
        set {
            newValue.withCString { ctext in
                nux_check_box_set_text(self.handle, ctext)
            }
        }
    }

    public var isChecked: Bool {
        get {
            return nux_check_box_is_checked(self.handle)
        }
        set {
            nux_check_box_set_checked(self.handle, newValue)
        }
    }

    deinit {
        nux_check_box_destroy(self.handle)
    }

    public var toggleEventHandler: CheckBoxToggleEventHandler

    public func toggle () -> Void {
        toggleEventHandler()
    }

    public override required init (
        handle: OpaquePointer
    ) {
        let cHandle = nux_check_box_create(handle)!
        self.toggleEventHandler = {}
        super.init(handle: cHandle)

        let payload = CheckBoxToggleEventPayload(
            sender: Unmanaged.passRetained(self).toOpaque()
        )
        let userData = Unmanaged.passRetained(payload).toOpaque()

        nux_check_box_set_toggle_event_handler(
            self.handle,
            handleNativeToggleEvent,
            userData
        )
    }
}
