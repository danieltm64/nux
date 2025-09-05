// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class Label: Widget, SimpleWidget {
    public var text: String {
        get {
            var size: Int32 = 0
            let cresult = nux_label_get_text(self.handle, &size)
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
                nux_label_set_text(self.handle, ctext)
            }
        }
    }

    deinit {
        nux_label_destroy(self.handle)
    }

    public override required init (
        handle: OpaquePointer
    ) {
        let cHandle = nux_label_create(handle)!
        super.init(handle: cHandle)
    }
}
