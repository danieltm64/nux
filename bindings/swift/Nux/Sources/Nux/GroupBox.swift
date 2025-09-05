// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class GroupBox: Widget, SimpleWidget {
    public var contentLayout: Layout {
        get {
            return self._contentLayout!
        }
    }

    public var title: String {
        get {
            var size: Int32 = 0
            let cresult = nux_group_box_get_title(self.handle, &size)
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
                nux_group_box_set_title(self.handle, ctext)
            }
        }
    }

    deinit {
        nux_group_box_destroy(self.handle)
    }

    public func addWidget<T: SimpleWidget> () -> T {
        var child: T = T(handle: self.handle!)
        nux_group_box_add_widget(self.handle, child.handle)
        return child
    }

    private var _contentLayout: Layout? = nil;

    public override required init (
        handle: OpaquePointer
    ) {
        let cHandle = nux_group_box_create(handle)!
        self._contentLayout = Layout(
            handle: nux_group_box_grab_content_layout(cHandle)
        )
        super.init(handle: cHandle)
    }
}
