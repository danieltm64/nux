// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public protocol SimpleWidget {
    init (handle: OpaquePointer)
    var handle: OpaquePointer? {
        get
        set
    }
}

public class Widget: WindowElement {
    public var isEnabled: Bool {
        get {
            return nux_widget_is_enabled(self.handle)
        }
        set {
            nux_widget_set_enabled(self.handle, newValue)
        }
    }

    public func show () {
        nux_widget_show(self.handle);
    }

    public func hide () {
        nux_widget_hide(self.handle);
    }

    public override init (
        handle: OpaquePointer
    ) {
        super.init(handle: handle)
    }
}
