// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Foundation
import CNux

public enum LayoutKind: Int32 {
    case Fixed
    case Flow
}

public enum LayoutAxis: Int32 {
    case Horizontal
    case Vertical
}

public enum LayoutDirection: Int32 {
    case Forward
    case Reverse
}

public class Layout: WindowElement {
    public init (
        parent: Layout,
        kind: LayoutKind,
        axis: LayoutAxis,
        direction: LayoutDirection
    ) {
        super.init(
            handle: nux_layout_create(
                parent.handle,
                nux_layout_kind_t(kind.rawValue),
                nux_layout_axis_t(axis.rawValue),
                nux_layout_direction_t(direction.rawValue)
            )
        )
    }

    public var parent: Layout {
        get {
            return Layout(handle: nux_layout_grab_parent(self.handle))
        }
    }

    public var kind: LayoutKind {
        get {
            return LayoutKind(
                rawValue: nux_layout_get_kind(self.handle).rawValue
            )!
        }
        set {
            nux_layout_set_kind(
                self.handle,
                nux_layout_kind_t(newValue.rawValue)
            )
        }
    }

    public var axis: LayoutAxis {
        get {
            return LayoutAxis(
                rawValue: nux_layout_get_axis(self.handle).rawValue
            )!
        }
        set {
            nux_layout_set_axis(
                self.handle,
                nux_layout_axis_t(newValue.rawValue)
            )
        }
    }

    public var direction: LayoutDirection {
        get {
            return LayoutDirection(
                rawValue: nux_layout_get_direction(self.handle).rawValue
            )!
        }
        set {
            nux_layout_set_direction(
                self.handle,
                nux_layout_direction_t(newValue.rawValue)
            )
        }
    }

    public func show () {
        nux_layout_show(self.handle)
    }

    public func hide () {
        nux_layout_hide(self.handle)
    }

    public func addWidget<T: SimpleWidget> () -> T {
        var child: T = T(handle: self.handle!)
        nux_layout_add_widget(self.handle, child.handle)
        return child
    }

    internal override init (
        handle: OpaquePointer
    ) {
        super.init(handle: handle)
    }
}
