// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.hpp>

#include "macos.hpp"

// Interfaces -----------------------------------------------------------------

@interface nux_application_delegate : NSObject<NSApplicationDelegate>
- (void)
applicationWillFinishLaunching:
(NSNotification*) notification;

- (void)
applicationDidFinishLaunching:
(NSNotification*) notification;

- (BOOL)
applicationShouldTerminateAfterLastWindowClosed:
(NSApplication*) sender;
@end // interface -------------------------------------------------------------

// Implementations ------------------------------------------------------------

@implementation nux_application_delegate
- (void)
applicationWillFinishLaunching:
    (NSNotification*) notification
{
    [[notification object] setActivationPolicy:
        NSApplicationActivationPolicyRegular
    ];
} // function -----------------------------------------------------------------

- (void)
applicationDidFinishLaunching:
    (NSNotification*) notification
{
    [[notification object] activateIgnoringOtherApps: YES];
} // function -----------------------------------------------------------------

- (BOOL)
applicationShouldTerminateAfterLastWindowClosed:
    (NSApplication*) sender
{
    return NO;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

namespace nux {

namespace impl {

NSApplication*
as_nsapplication (
    void* application
) {
    return static_cast<NSApplication*>(application);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ---------------------------------------------------------- nux::application

// Constructors and Destructor ------------------------------------------------

application::application (
    int NUX_UNUSED(argc),
    char** NUX_UNUSED(argv)
)
    : m_native_handle{new application_native_handle{}}
    , m_is_running{false}
{
    g_app = this;

    m_native_handle->shared_application = [NSApplication sharedApplication];
    [impl::as_nsapplication(m_native_handle->shared_application) setDelegate:
        [[nux_application_delegate alloc] init]
    ];
    [
        impl::as_nsapplication(m_native_handle->shared_application)
            finishLaunching
    ];
} // function -----------------------------------------------------------------

application::~application ()
noexcept
{
    delete m_native_handle;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

int
application::run ()
{
    m_is_running = true;
    while (!m_native_handle->window_associations.empty()) {
        NSEvent* event = [
            impl::as_nsapplication(m_native_handle->shared_application)
                nextEventMatchingMask:
                    NSEventMaskAny
                    untilDate:[NSDate distantPast]
                    inMode:NSDefaultRunLoopMode
                    dequeue:YES
        ];
        if (event != nil) {
            [
                impl::as_nsapplication(m_native_handle->shared_application)
                    sendEvent:
                        event
            ];
        } else {
            for (
                auto& current_association
                    : m_native_handle->window_associations
            ) {
                impl::update_window(current_association.second);
            }
        }
    }
    m_is_running = false;
    return 0;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
