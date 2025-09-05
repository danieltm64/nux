// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public typealias PushButtonTriggerEventHandler = () -> Void

private class PushButtonTriggerEventPayload {
    public let sender: UnsafeMutableRawPointer
    init (
        sender: UnsafeMutableRawPointer
    ) {
        self.sender = sender
    }
}

private func handleNativeTriggerEvent (
    nativeSender: OpaquePointer?,
    userData: UnsafeMutableRawPointer?
) {
    if let userData = userData {
        let payload = Unmanaged<PushButtonTriggerEventPayload>.fromOpaque(
            userData
        ).takeUnretainedValue()
        let sender = Unmanaged<PushButton>.fromOpaque(
            payload.sender
        ).takeUnretainedValue()
        sender.trigger()
    }
}

public class PushButton: Widget, SimpleWidget {
    public var text: String {
        get {
            var size: Int32 = 0
            let cresult = nux_push_button_get_text(self.handle, &size)
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
                nux_push_button_set_text(self.handle, ctext)
            }
        }
    }

    public var triggerEventHandler: PushButtonTriggerEventHandler

    public func trigger () -> Void {
        triggerEventHandler()
    }

    public override required init (
        handle: OpaquePointer
    ) {
        let cHandle = nux_push_button_create(handle)!
        self.triggerEventHandler = {}
        super.init(handle: cHandle)

        let payload = PushButtonTriggerEventPayload(
            sender: Unmanaged.passRetained(self).toOpaque()
        )
        let userData = Unmanaged.passRetained(payload).toOpaque()

        nux_push_button_set_trigger_event_handler(
            self.handle,
            handleNativeTriggerEvent,
            userData
        )
    }
}
