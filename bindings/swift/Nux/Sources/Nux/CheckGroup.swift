// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class CheckGroup {
    public init () {
        self.handle = nux_check_group_create()
    }

    deinit {
        nux_check_group_destroy(self.handle)
    }

    internal var handle: OpaquePointer? = nil
}
