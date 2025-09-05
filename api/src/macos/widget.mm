// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/widget.hpp>

#include "macos.hpp"

// Interfaces -----------------------------------------------------------------

@interface nux_stack_view : NSStackView
- (BOOL)
isFlipped;
@end // interface -------------------------------------------------------------

@interface nux_box_view : NSView
- (BOOL)
isFlipped;

- (void)
handleAction:
    (NSView*) sender;
@end // interface -------------------------------------------------------------

@interface nux_text_field_cell : NSTextFieldCell
@end // interface -------------------------------------------------------------

@interface nux_text_field : NSTextField
@end // interface -------------------------------------------------------------

@interface nux_graphics_box : NSOpenGLView
@end // interface -------------------------------------------------------------

namespace nux {

namespace impl {

void
forward_action_to_widget (
    NSView* widget_handle
);

void
forward_resize_event_to_widget (
    NSView* widget_handle
);

void
forward_render_event_to_widget (
    NSView* widget_handle
);

widget_native_handle
create_widget (
    NSResponder* parent_handle,
    native_widget_kind kind
)
noexcept
{
    NSView* result;
    if (kind == native_widget_kind::label) {
        result = [nux_text_field labelWithString: @""];
    } else if (kind == native_widget_kind::group_box) {
        result = [[NSBox alloc] init];
        [result setContentView: [[nux_box_view alloc] init]];
        reinterpret_cast<NSBox*>(result).contentViewMargins = NSMakeSize(0, 0);
    } else if (kind == native_widget_kind::graphics_box) {
        result = [[nux_graphics_box alloc] init];
    } else {
        result = [
            [NSButton alloc] init
        ];
    }
    switch (kind) {
        case native_widget_kind::push_button:
            [static_cast<NSButton*>(result) setBezelStyle: NSBezelStyleFlexiblePush];
            break;
        case native_widget_kind::check_box:
            [static_cast<NSButton*>(result) setButtonType: NSButtonTypeSwitch];
            break;
        case native_widget_kind::radio_button:
            [static_cast<NSButton*>(result) setButtonType: NSButtonTypeRadio];
            break;
    }
    [result setHidden: YES];
    if (
        kind != native_widget_kind::group_box
            && kind != native_widget_kind::graphics_box
    ) {
        if ([parent_handle isKindOfClass:[NSWindow class]]) {
            [result setTarget: reinterpret_cast<NSWindow*>(parent_handle)];
        } else if ([parent_handle isKindOfClass:[NSBox class]]) {
            [
                result setTarget:
                    reinterpret_cast<NSBox*>(parent_handle).contentView
            ];
        }
        [result setAction: @selector(handleAction:)];
    }
    NSView* parent_content_view{nullptr};
    if ([parent_handle isKindOfClass:[NSWindow class]]) {
        parent_content_view
            = static_cast<NSWindow*>(parent_handle).contentView;
    } else if ([parent_handle isKindOfClass:[NSBox class]]) {
        parent_content_view
            = static_cast<NSBox*>(parent_handle).contentView;
    }
    if (kind == native_widget_kind::label) {
        auto nstextfield{static_cast<NSTextField*>(result)};
        [nstextfield setCell: [[nux_text_field_cell alloc] init]];
        [nstextfield setStringValue: @""];
        [parent_content_view addSubview: result];
    }
    [parent_content_view addSubview: result];
    return {parent_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- nux::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    layout& enclosing_layout
)
    : m_native_handle{
          new widget_native_handle{
              enclosing_layout.grab_enclosing_window_handle().nux_window_handle,
              nullptr
          }
      }
    , m_enclosing_layout{&enclosing_layout}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
widget::get_position (
    int& x,
    int& y
)
const noexcept
{
    auto position{[grab_native_handle().widget_handle frame].origin};
    x = position.x;
    y = position.y;
} // function -----------------------------------------------------------------

void
widget::get_size (
    int& width,
    int& height
)
const noexcept
{
    auto size{[grab_native_handle().widget_handle frame].size};
    width = size.width;
    height = size.height;
} // function -----------------------------------------------------------------

bool
widget::is_enabled ()
const noexcept
{
    return [grab_native_handle().widget_handle isEnabled];
} // function -----------------------------------------------------------------

void
widget::set_enabled (
    bool new_enabled
)
noexcept
{
    [grab_native_handle().widget_handle setEnabled: new_enabled];
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    [grab_native_handle().widget_handle setHidden: NO];
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    [grab_native_handle().widget_handle setHidden: YES];
} // function -----------------------------------------------------------------

void
widget::handle_dpi_update_event (
    int NUX_UNUSED(old_dpi),
    int NUX_UNUSED(new_dpi)
) {
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    layout& enclosing_layout,
    widget_native_handle&& widget_handle
)
    : m_enclosing_layout{&enclosing_layout}
{
    m_native_handle = new widget_native_handle{std::move(widget_handle)};
} // function -----------------------------------------------------------------

void
widget::get_preferred_size_generically (
    const widget_native_handle& native_handle,
    int& width,
    int& height
)
noexcept
{
    NSSize preferred_size{
        [native_handle.widget_handle fittingSize]
    };
    width = preferred_size.width;
    height = preferred_size.height;
} // function -----------------------------------------------------------------

void
widget::set_position_forcefully (
    int new_x,
    int new_y
)
noexcept
{
    [grab_native_handle().widget_handle setFrameOrigin:
        NSPoint{
            static_cast<CGFloat>(new_x),
            static_cast<CGFloat>(new_y),
        }
    ];
} // function -----------------------------------------------------------------

void
widget::set_size_forcefully (
    int new_width,
    int new_height
)
noexcept
{
    [grab_native_handle().widget_handle setFrameSize:
        NSSize{
            static_cast<CGFloat>(new_width),
            static_cast<CGFloat>(new_height)
        }
    ];
} // function -----------------------------------------------------------------

int
widget::get_parent_dpi ()
const noexcept
{
    NSScreen* screen{
        [
            grab_enclosing_layout().grab_enclosing_window_handle()
                .nux_window_handle
                    screen
        ]
    };
    NSDictionary* description{[screen deviceDescription]};
    NSSize pixelSize{[[description objectForKey: NSDeviceSize] sizeValue]};
    NSNumber* screenNumber{[description objectForKey:@"NSScreenNumber"]};
    CGSize physicalSizeMM{
        CGDisplayScreenSize(
            [screenNumber unsignedIntValue]
        )
    };
    CGFloat widthInPixels{pixelSize.width};
    CGFloat widthInInches{physicalSizeMM.width / 25.4};
    return widthInPixels / widthInInches;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// Implementations ------------------------------------------------------------

@implementation nux_stack_view
- (BOOL)
isFlipped
{
    return YES;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

@implementation nux_box_view
- (BOOL)
isFlipped
{
    return YES;
} // function -----------------------------------------------------------------

- (void)
handleAction:
    (NSView*) sender
{
    nux::impl::forward_action_to_widget(sender);
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

@implementation nux_text_field_cell
- (NSRect)
drawingRectForBounds:
    (NSRect) bounds
{
    NSRect target_rect{[super drawingRectForBounds: bounds]};
    NSSize text_size{[self cellSizeForBounds: bounds]};
    double height_difference{target_rect.size.height - text_size.height};
    if (height_difference > 0) {
        target_rect.origin.y += (height_difference / 2);
    }
    return target_rect;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

@implementation nux_text_field
- (NSSize)sizeForProgrammaticText:(NSString *)string
{
    NSFont *font{self.font ?: [NSFont systemFontOfSize:[NSFont systemFontSize]]};
    NSDictionary *attributes{@{NSFontAttributeName: font}};
    NSSize stringSize{[string sizeWithAttributes:attributes]};
    stringSize.width += 5.0;
    return stringSize;
}

- (void)setStringValue:(NSString *)stringValue
{
    [super setStringValue:stringValue];
    [self invalidateIntrinsicContentSize];
}

- (NSSize)intrinsicContentSize
{
    NSString *text{self.stringValue};
    if (text.length == 0 && self.placeholderString.length > 0) {
        return [self sizeForProgrammaticText:self.placeholderString];
    }
    return [self sizeForProgrammaticText: text];
}
@end // implementation --------------------------------------------------------

@implementation nux_graphics_box
- (id)
initWithFrame:
    (NSRect) frame
{
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFANoRecovery,
        0
    };
    NSOpenGLPixelFormat* pixelFormat{
        [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes]
    };
    self = [super initWithFrame: frame pixelFormat: pixelFormat];
    return self;
} // function -----------------------------------------------------------------

- (void)
reshape
{
    nux::impl::forward_resize_event_to_widget(self);
} // function -----------------------------------------------------------------

- (void)
drawRect:
    (NSRect) dirtyRect
{
    nux::impl::forward_render_event_to_widget(self);
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------
