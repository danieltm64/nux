// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public class Application {
    public init (
        args: [String]
    ) {
        let cargs = CommandLine.arguments.map { strdup($0) }
        defer {
            for pointer in cargs where pointer != nil {
                free(pointer)
            }
        }
        cargs.withUnsafeBufferPointer { buffer in
            let argc = Int32(buffer.count)
            let argv = UnsafeMutablePointer(mutating: buffer.baseAddress)
            self.handle = nux_application_create(argc, argv);
        }
    }

    deinit {
        nux_application_destroy(handle);
    }

    public static var encoding: Encoding {
        return Encoding(rawValue: nux_application_get_encoding().rawValue)!;
    }

    public func run () -> Int32 {
        return nux_application_run(handle);
    }

    internal var handle: OpaquePointer? = nil;
}
