// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/window.hpp>
#include <nux/application.hpp>

#include "qt.hpp"

namespace nux {

namespace impl {

// Free Functions -------------------------------------------------------------

key
translate_key_code (
    Qt::Key key_code,
    Qt::KeyboardModifiers modifiers
) {
    switch (key_code) {
        case Qt::Key_F1:
            return key::f1;
        case Qt::Key_F2:
            return key::f2;
        case Qt::Key_F3:
            return key::f3;
        case Qt::Key_F4:
            return key::f4;
        case Qt::Key_F5:
            return key::f5;
        case Qt::Key_F6:
            return key::f6;
        case Qt::Key_F7:
            return key::f7;
        case Qt::Key_F8:
            return key::f8;
        case Qt::Key_F9:
            return key::f9;
        case Qt::Key_F10:
            return key::f10;
        case Qt::Key_F11:
            return key::f11;
        case Qt::Key_F12:
            return key::f12;
        case Qt::Key_F13:
            return key::f13;
        case Qt::Key_F14:
            return key::f14;
        case Qt::Key_F15:
            return key::f15;
        case Qt::Key_F16:
            return key::f16;
        case Qt::Key_F17:
            return key::f17;
        case Qt::Key_F18:
            return key::f18;
        case Qt::Key_F19:
            return key::f19;
        case Qt::Key_F20:
            return key::f20;
        case Qt::Key_F21:
            return key::f21;
        case Qt::Key_F22:
            return key::f22;
        case Qt::Key_F23:
            return key::f23;
        case Qt::Key_F24:
            return key::f24;
        case Qt::Key_0:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_0 : key::number_0;
        case Qt::Key_1:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_1 : key::number_1;
        case Qt::Key_2:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_2 : key::number_2;
        case Qt::Key_3:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_3 : key::number_3;
        case Qt::Key_4:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_4 : key::number_4;
        case Qt::Key_5:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_5 : key::number_5;
        case Qt::Key_6:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_6 : key::number_6;
        case Qt::Key_7:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_7 : key::number_7;
        case Qt::Key_8:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_8 : key::number_8;
        case Qt::Key_9:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_9 : key::number_9;
        case Qt::Key_A:
            return key::a;
        case Qt::Key_B:
            return key::b;
        case Qt::Key_C:
            return key::c;
        case Qt::Key_D:
            return key::d;
        case Qt::Key_E:
            return key::e;
        case Qt::Key_F:
            return key::f;
        case Qt::Key_G:
            return key::g;
        case Qt::Key_H:
            return key::h;
        case Qt::Key_I:
            return key::i;
        case Qt::Key_J:
            return key::j;
        case Qt::Key_K:
            return key::k;
        case Qt::Key_L:
            return key::l;
        case Qt::Key_M:
            return key::m;
        case Qt::Key_N:
            return key::n;
        case Qt::Key_O:
            return key::o;
        case Qt::Key_P:
            return key::p;
        case Qt::Key_Q:
            return key::q;
        case Qt::Key_R:
            return key::r;
        case Qt::Key_S:
            return key::s;
        case Qt::Key_T:
            return key::t;
        case Qt::Key_U:
            return key::u;
        case Qt::Key_V:
            return key::v;
        case Qt::Key_W:
            return key::w;
        case Qt::Key_X:
            return key::x;
        case Qt::Key_Y:
            return key::y;
        case Qt::Key_Z:
            return key::z;
        case Qt::Key_Space:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

nux_main_window*
as_nux_main_window (
    void* nux_main_window_ptr
)
noexcept
{
    return static_cast<nux_main_window*>(nux_main_window_ptr);
} // function -----------------------------------------------------------------

void
forward_key_down_event_to_window (
    nux_main_window* nux_main_window_handle,
    QKeyEvent* event
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == nux_main_window_handle) {
            key_event ev{
                key_event_type::key_down,
                translate_key_code(
                  static_cast<Qt::Key>(event->key()),
                  event->modifiers()
                )
            };
            current_association.second->handle_key_down_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_key_up_event_to_window (
    nux_main_window* nux_main_window_handle,
    QKeyEvent* event
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == nux_main_window_handle) {
            key_event ev{
                key_event_type::key_up,
                translate_key_code(
                  static_cast<Qt::Key>(event->key()),
                  event->modifiers()
                )
            };
            current_association.second->handle_key_up_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    void* nux_main_window_ptr
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == as_nux_main_window(nux_main_window_ptr)) {
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
bool
forward_close_event_to_window (
    nux_main_window* nux_main_window_handle
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (
        auto current_association{std::begin(window_associations)};
        current_association != std::end(window_associations);
        ++current_association
    ) {
        if (current_association->first == nux_main_window_handle) {
            close_event ev{true};
            current_association->second->handle_close_event(ev);
            if (ev.should_close()) {
                window_associations.erase(current_association);
                return false;
            } else {
                return true;
            }
        }
    }
} // function -----------------------------------------------------------------
NUX_DISABLE_WARNING_POP

// ------------------------------------------------ nux::impl::nux_main_window

// Constructors and Destructor ------------------------------------------------

nux_main_window::nux_main_window (
    QWidget* parent,
    Qt::WindowFlags flags
)
    : QMainWindow{parent, flags}
{
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

void
nux_main_window::keyPressEvent (
    QKeyEvent* event
) {
    forward_key_down_event_to_window(this, event);
} // function -----------------------------------------------------------------

void
nux_main_window::keyReleaseEvent (
    QKeyEvent* event
) {
    forward_key_up_event_to_window(this, event);
} // function -----------------------------------------------------------------

void
nux_main_window::resizeEvent (
    QResizeEvent* NUX_UNUSED(event)
) {
    forward_resize_event_to_window(this);
} // function -----------------------------------------------------------------

void
nux_main_window::closeEvent (
    QCloseEvent* event
) {
    if (forward_close_event_to_window(this)) {
        event->ignore();
    }
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

    m_native_handle->nux_main_window_handle = new impl::nux_main_window();
    set_title(initial_title);
    m_native_handle->nux_main_window_handle->resize(
        initial_width,
        initial_height
    );
    if (initial_mode == window_mode::maximized) {
        m_native_handle->nux_main_window_handle->setWindowState(
            Qt::WindowMaximized
        );
    } else if (initial_mode == window_mode::minimized) {
        m_native_handle->nux_main_window_handle->setWindowState(
            Qt::WindowMinimized
        );
    }
    m_native_handle->nux_main_window_handle->setAttribute(
        Qt::WA_DeleteOnClose
    );

    m_root_layout.m_enclosing_window_handle = m_native_handle;

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle->nux_main_window_handle,
        this
    );
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

nux::string
window::get_title ()
const
{
    return impl::to_nux_string(
        m_native_handle->nux_main_window_handle->windowTitle()
    );
} // function -----------------------------------------------------------------

void
window::set_title (
    nux::string_view new_title
) {
    m_native_handle->nux_main_window_handle->setWindowTitle(
        impl::to_qstring(new_title)
    );
} // function -----------------------------------------------------------------

void
window::get_size (
    int& width,
    int& height
)
const noexcept
{
    width = m_native_handle->nux_main_window_handle->width();
    height = m_native_handle->nux_main_window_handle->height();
} // function -----------------------------------------------------------------

void
window::set_size (
    int new_width,
    int new_height
)
noexcept
{
    m_native_handle->nux_main_window_handle->resize(
        new_width,
        new_height
    );
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
window::show ()
noexcept
{
    if (m_native_handle->nux_main_window_handle->isVisible()) {
        return;
    }

    m_native_handle->nux_main_window_handle->show();
} // function -----------------------------------------------------------------

void
window::hide ()
noexcept
{
    m_native_handle->nux_main_window_handle->hide();
} // function -----------------------------------------------------------------

void
window::close ()
noexcept
{
    m_native_handle->nux_main_window_handle->close();
} // function -----------------------------------------------------------------

void
window::center ()
noexcept
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    QRect windowGeometry = m_native_handle->nux_main_window_handle->frameGeometry();
    m_native_handle->nux_main_window_handle->move(
        screenGeometry.center() - windowGeometry.center()
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
