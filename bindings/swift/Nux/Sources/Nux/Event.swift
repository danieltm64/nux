// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public enum EventType: Int32 {
    case KeyEvent
    case CloseEvent
}

public class Event {
    public init (
        eventType: EventType
    ) {
        self.handle = nux_event_create(nux_event_type_t(eventType.rawValue))
    }

    deinit {
        nux_event_destroy(self.handle)
    }

    public var eventType: EventType {
        get {
            return EventType(
                rawValue: nux_event_get_event_type(self.handle).rawValue
            )!
        }
    }

    public var handle: OpaquePointer? = nil
}
