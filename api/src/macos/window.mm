// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/window.hpp>
#include <nux/application.hpp>

#include "macos.hpp"

// Interfaces -----------------------------------------------------------------

@interface nux_window : NSWindow
- (void)
keyDown:
    (NSEvent*) event;

- (void)
keyUp:
    (NSEvent*) event;

- (void)
handleAction:
    (NSView*) sender;

- (void)
viewFrameDidChange:
    (NSNotification*) notification;
@end // interface -------------------------------------------------------------

@interface nux_window_delegate : NSObject<NSWindowDelegate>
- (void)
windowDidResize:
    (NSNotification*) notification;

- (BOOL)
windowShouldClose:
    (NSWindow*) sender;
@end // interface -------------------------------------------------------------

@interface nux_view : NSView
- (BOOL)
isFlipped;
@end // interface -------------------------------------------------------------

namespace nux {

namespace impl {

key
translate_key_code (
    unsigned short key_code
) {
    switch (key_code) {
        case 122:
            return key::f1;
        case 120:
            return key::f2;
        case 99:
            return key::f3;
        case 118:
            return key::f4;
        case 96:
            return key::f5;
        case 97:
            return key::f6;
        case 98:
            return key::f7;
        case 100:
            return key::f8;
        case 101:
            return key::f9;
        case 109:
            return key::f10;
        case 103:
            return key::f11;
        case 111:
            return key::f12;
        case 105:
            return key::f13;
        case 107:
            return key::f14;
        case 113:
            return key::f15;
        case 106:
            return key::f16;
        case 64:
            return key::f17;
        case 79:
            return key::f18;
        case 80:
            return key::f19;
        case 90:
            return key::f20;
        case 29:
            return key::number_0;
        case 18:
            return key::number_1;
        case 19:
            return key::number_2;
        case 20:
            return key::number_3;
        case 21:
            return key::number_4;
        case 23:
            return key::number_5;
        case 22:
            return key::number_6;
        case 26:
            return key::number_7;
        case 28:
            return key::number_8;
        case 25:
            return key::number_9;
        case 82:
            return key::numpad_0;
        case 83:
            return key::numpad_1;
        case 84:
            return key::numpad_2;
        case 85:
            return key::numpad_3;
        case 86:
            return key::numpad_4;
        case 87:
            return key::numpad_5;
        case 88:
            return key::numpad_6;
        case 89:
            return key::numpad_7;
        case 91:
            return key::numpad_8;
        case 92:
            return key::numpad_9;
        case 0:
            return key::a;
        case 11:
            return key::b;
        case 8:
            return key::c;
        case 2:
            return key::d;
        case 14:
            return key::e;
        case 3:
            return key::f;
        case 5:
            return key::g;
        case 4:
            return key::h;
        case 34:
            return key::i;
        case 38:
            return key::j;
        case 40:
            return key::k;
        case 37:
            return key::l;
        case 46:
            return key::m;
        case 45:
            return key::n;
        case 31:
            return key::o;
        case 35:
            return key::p;
        case 12:
            return key::q;
        case 15:
            return key::r;
        case 1:
            return key::s;
        case 17:
            return key::t;
        case 32:
            return key::u;
        case 9:
            return key::v;
        case 13:
            return key::w;
        case 7:
            return key::x;
        case 16:
            return key::y;
        case 6:
            return key::z;
        case 49:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

nux_window*
as_nux_window (
    void* nux_window_ptr
)
noexcept
{
    return static_cast<nux_window*>(nux_window_ptr);
} // function -----------------------------------------------------------------

void
forward_key_down_event_to_window (
    nux_window* nux_window_ptr,
    NSEvent* event
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == nux_window_ptr) {
            key_event ev{
                key_event_type::key_down,
                translate_key_code([event keyCode])
            };
            current_association.second->handle_key_down_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_key_up_event_to_window (
    nux_window* nux_window_ptr,
    NSEvent* event
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == nux_window_ptr) {
            key_event ev{
                key_event_type::key_up,
                translate_key_code([event keyCode])
            };
            current_association.second->handle_key_up_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    void* nux_window_ptr
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == as_nux_window(nux_window_ptr)) {
            current_association.second->update_root_layout();
            current_association.second->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

/*
    The reason for disabling this warning is that the compiler doesn't
    realize that this function is only called with known window handles,
    which means that the for loop will always find a match and then return
    true or false, so control will never reach the end of this non-void
    function.
*/
NUX_DISABLE_WARNING_PUSH
NUX_DISABLE_WARNING(NUX_WARNING_ID_END_OF_NON_VOID)
BOOL
forward_close_event_to_window (
    nux_window* nux_window_ptr
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (
        auto current_association{std::begin(window_associations)};
        current_association != std::end(window_associations);
        ++current_association
    ) {
        if (current_association->first == nux_window_ptr) {
            close_event ev{true};
            current_association->second->handle_close_event(ev);
            if (ev.should_close()) {
                window_associations.erase(current_association);
                return YES;
            } else {
                return NO;
            }
        }
    }
} // function -----------------------------------------------------------------
NUX_DISABLE_WARNING_POP

widget*
find_widget (
    NSView* widget_handle,
    const std::vector<std::unique_ptr<window_element>>& window_elements
) {
    widget* target{nullptr};
    for (const auto& current_window_element : window_elements) {
        auto layout_ptr{dynamic_cast<layout*>(current_window_element.get())};
        if (layout_ptr) {
            target = find_widget(widget_handle, layout_ptr->grab_children());
            if (target) {
                return target;
            }
        } else {
            target = static_cast<widget*>(current_window_element.get());
            if (
                target->grab_native_handle().widget_handle == widget_handle
            ) {
                return target;
            } else {
                auto group_box_ptr{
                    dynamic_cast<group_box*>(current_window_element.get())
                };
                if (group_box_ptr) {
                    target = find_widget(
                        widget_handle,
                        group_box_ptr->grab_content_layout().grab_children()
                    );
                    if (target) {
                        return target;
                    }
                }
            }
        }
    }
    return nullptr;
} // function -----------------------------------------------------------------

void
forward_action_to_widget (
    NSView* widget_handle
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    widget* widget_ptr{nullptr};
    for (const auto& current_association : window_associations) {
        widget_ptr = find_widget(
            widget_handle,
            current_association.second->grab_root_layout().grab_children()
        );
        if (widget_ptr) {
            break;
        }
    }
    auto push_button_ptr{dynamic_cast<push_button*>(widget_ptr)};
    if (push_button_ptr) {
        push_button_ptr->trigger();
        return;
    }
    auto check_box_ptr{dynamic_cast<check_box*>(widget_ptr)};
    if (check_box_ptr) {
        check_box_ptr->toggle();
        return;
    }
    auto radio_button_ptr{dynamic_cast<radio_button*>(widget_ptr)};
    radio_button* active_element;
    if (
        radio_button_ptr
            && (
                active_element = (
                    radio_button_ptr->grab_group().get_active_element()
                )
            ) != radio_button_ptr
    ) {
        if (active_element) {
            active_element->set_checked(false);
            active_element->toggle();
        }
        radio_button_ptr->toggle();
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_widget (
    NSView* widget_handle
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    widget* widget_ptr{nullptr};
    for (const auto& current_association : window_associations) {
        widget_ptr = find_widget(
            widget_handle,
            current_association.second->grab_root_layout().grab_children()
        );
        if (widget_ptr) {
            widget_ptr->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_render_event_to_widget (
    NSView* widget_handle
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    widget* widget_ptr{nullptr};
    for (const auto& current_association : window_associations) {
        widget_ptr = find_widget(
            widget_handle,
            current_association.second->grab_root_layout().grab_children()
        );
        if (widget_ptr) {
            break;
        }
    }
    auto graphics_box_ptr{dynamic_cast<graphics_box*>(widget_ptr)};
    graphics_box_ptr->render();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- nux::window

// Constructors and Destructor ------------------------------------------------

window::window (
    nux::string_view initial_title,
    int initial_width,
    int initial_height,
    window_mode initial_mode
)
    : m_native_handle{new window_native_handle{}}
{
    auto& application_native_handle{app()->grab_native_handle()};

    m_native_handle->nux_window_handle = [[nux_window alloc]
        initWithContentRect:
            NSRect{
                {
                    0.0,
                    0.0
                },
                {
                    static_cast<CGFloat>(initial_width),
                    static_cast<CGFloat>(initial_height)
                }
            }
            styleMask:
                NSWindowStyleMaskTitled
                    | NSWindowStyleMaskClosable
                    | NSWindowStyleMaskMiniaturizable
                    | NSWindowStyleMaskResizable
            backing: NSBackingStoreBuffered
            defer: NO
    ];

    nux_window* w{impl::as_nux_window(m_native_handle->nux_window_handle)};

    [w setDelegate: [[nux_window_delegate alloc] init]];
    [w setContentView: [[nux_view alloc] init]];
    [w setTitle: impl::to_nsstring(initial_title)];
    [w center];
    if (initial_mode == window_mode::maximized) {
        [w zoom: w];
    }
    else if (initial_mode == window_mode::minimized) {
        [w miniaturize: w];
    }

    m_root_layout.m_enclosing_window_handle = m_native_handle;

    m_native_handle->has_been_shown = false;

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle->nux_window_handle,
        this
    );
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
window::get_size (
    int& width,
    int& height
)
const noexcept
{
    auto size{
        [[impl::as_nux_window(m_native_handle->nux_window_handle) contentView]
            frame].size
    };
    width = size.width;
    height = size.height;
} // function -----------------------------------------------------------------

void
window::set_size (
    int new_width,
    int new_height
)
noexcept
{
    [impl::as_nux_window(m_native_handle->nux_window_handle) setContentSize: NSMakeSize(new_width, new_height)];
} // function -----------------------------------------------------------------

nux::string
window::get_title ()
const {
    return impl::to_nux_string([m_native_handle->nux_window_handle title]);
} // function -----------------------------------------------------------------

void
window::set_title (
    nux::string_view new_title
) {
    [
        m_native_handle->nux_window_handle setTitle:
            impl::to_nsstring(new_title)
    ];
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
window::show ()
noexcept
{
    if ([impl::as_nux_window(m_native_handle->nux_window_handle) isVisible]) {
        return;
    }

    if (!m_native_handle->has_been_shown) {
        impl::forward_resize_event_to_window(
            m_native_handle->nux_window_handle
        );
        m_native_handle->has_been_shown = true;
    }

    [impl::as_nux_window(m_native_handle->nux_window_handle)
        makeKeyAndOrderFront:
            nil
    ];
} // function -----------------------------------------------------------------

void
window::hide ()
noexcept
{
    nux_window* window_handle{
        impl::as_nux_window(m_native_handle->nux_window_handle)
    };
    [window_handle orderOut: window_handle];
} // function -----------------------------------------------------------------

void
window::close ()
noexcept
{
    nux_window* window_handle{
        impl::as_nux_window(m_native_handle->nux_window_handle)
    };
    [window_handle performClose: window_handle];
} // function -----------------------------------------------------------------

void
window::center ()
noexcept
{
    nux_window* window_handle{
        impl::as_nux_window(m_native_handle->nux_window_handle)
    };
    [window_handle center];
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// Implementations ------------------------------------------------------------

@implementation nux_window
- (void)
keyDown:
    (NSEvent*) event
{
     nux::impl::forward_key_down_event_to_window(self, event);
} // function -----------------------------------------------------------------

- (void)
keyUp:
    (NSEvent*) event
{
     nux::impl::forward_key_up_event_to_window(self, event);
} // function -----------------------------------------------------------------

- (void)
handleAction:
    (NSView*) sender
{
    nux::impl::forward_action_to_widget(sender);
} // function -----------------------------------------------------------------

- (void)
viewFrameDidChange:
    (NSNotification*) notification
{
    nux::impl::forward_resize_event_to_widget([notification object]);
}
@end // implementation --------------------------------------------------------

@implementation nux_window_delegate
- (void)
windowDidResize:
    (NSNotification*) notification
{
    nux::impl::forward_resize_event_to_window([notification object]);
} // function -----------------------------------------------------------------

- (BOOL)
windowShouldClose:
    (NSWindow*) sender
{
    return nux::impl::forward_close_event_to_window(
        nux::impl::as_nux_window(sender)
    );
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

@implementation nux_view
- (BOOL)
isFlipped
{
    return YES;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------
