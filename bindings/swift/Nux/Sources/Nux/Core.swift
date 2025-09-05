// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

internal typealias CCallback = @convention(c) (
    OpaquePointer?,
    UnsafeMutableRawPointer?
) -> Void
