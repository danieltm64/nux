// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class CloseEvent {
    public init (
        shouldClose: Bool
    ) {
        self.handle = nux_close_event_create(shouldClose)
        self.ownsHandle = true
    }

    public init (
        handle: OpaquePointer?
    ) {
        self.handle = handle
        self.ownsHandle = false
    }

    deinit {
        if self.ownsHandle {
            nux_close_event_destroy(self.handle)
        }
    }

    public var shouldClose: Bool {
        get {
            return nux_close_event_should_close(self.handle)
        }
        set {
            nux_close_event_set_should_close(self.handle, newValue)
        }
    }

    public var handle: OpaquePointer? = nil
    private var ownsHandle: Bool
}
