// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public typealias RadioButtonToggleEventHandler = () -> Void

private class RadioButtonToggleEventPayload {
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
        let payload = Unmanaged<RadioButtonToggleEventPayload>.fromOpaque(
            userData
        ).takeUnretainedValue()
        let sender = Unmanaged<RadioButton>.fromOpaque(
            payload.sender
        ).takeUnretainedValue()
        sender.toggle()
    }
}

public class RadioButton: Widget {
    public var text: String {
        get {
            var size: Int32 = 0
            let cresult = nux_radio_button_get_text(self.handle, &size)
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
                nux_radio_button_set_text(self.handle, ctext)
            }
        }
    }

    public var isChecked: Bool {
        get {
            return nux_radio_button_is_checked(self.handle)
        }
        set {
            nux_radio_button_set_checked(self.handle, newValue)
        }
    }

    deinit {
        nux_radio_button_destroy(self.handle)
    }

    public var toggleEventHandler: RadioButtonToggleEventHandler

    public func toggle () -> Void {
        toggleEventHandler()
    }

    internal init (
        handle: OpaquePointer,
        group: CheckGroup
    ) {
        let cHandle = nux_radio_button_create(handle, group.handle)!
        self.toggleEventHandler = {}
        super.init(handle: cHandle)

        let payload = RadioButtonToggleEventPayload(
            sender: Unmanaged.passRetained(self).toOpaque()
        )
        let userData = Unmanaged.passRetained(payload).toOpaque()

        nux_radio_button_set_toggle_event_handler(
            self.handle,
            handleNativeToggleEvent,
            userData
        )
    }
}

extension Layout
{
    public func addWidget(group: CheckGroup) -> RadioButton {
        var child = RadioButton(handle: self.handle!, group: group)
        nux_layout_add_widget(self.handle, child.handle)
        return child
    }
}

extension GroupBox
{
    public func addWidget(group: CheckGroup) -> RadioButton {
        var child = RadioButton(handle: self.handle!, group: group)
        nux_group_box_add_widget(self.handle, child.handle)
        return child
    }
}
