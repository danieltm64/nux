// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/window.hpp>
#include <nux/application.hpp>

#include "windows.hpp"

namespace nux {

namespace impl {

key
translate_key_code (
    WPARAM key_code
) {
    switch (key_code) {
        case VK_F1:
            return key::f1;
        case VK_F2:
            return key::f2;
        case VK_F3:
            return key::f3;
        case VK_F4:
            return key::f4;
        case VK_F5:
            return key::f5;
        case VK_F6:
            return key::f6;
        case VK_F7:
            return key::f7;
        case VK_F8:
            return key::f8;
        case VK_F9:
            return key::f9;
        case VK_F10:
            return key::f10;
        case VK_F11:
            return key::f11;
        case VK_F12:
            return key::f12;
        case VK_F13:
            return key::f13;
        case VK_F14:
            return key::f14;
        case VK_F15:
            return key::f15;
        case VK_F16:
            return key::f16;
        case VK_F17:
            return key::f17;
        case VK_F18:
            return key::f18;
        case VK_F19:
            return key::f19;
        case VK_F20:
            return key::f20;
        case VK_F21:
            return key::f21;
        case VK_F22:
            return key::f22;
        case VK_F23:
            return key::f23;
        case VK_F24:
            return key::f24;
        case 0x30:
            return key::number_0;
        case 0x31:
            return key::number_1;
        case 0x32:
            return key::number_2;
        case 0x33:
            return key::number_3;
        case 0x34:
            return key::number_4;
        case 0x35:
            return key::number_5;
        case 0x36:
            return key::number_6;
        case 0x37:
            return key::number_7;
        case 0x38:
            return key::number_8;
        case 0x39:
            return key::number_9;
        case VK_NUMPAD0:
            return key::numpad_0;
        case VK_NUMPAD1:
            return key::numpad_1;
        case VK_NUMPAD2:
            return key::numpad_2;
        case VK_NUMPAD3:
            return key::numpad_3;
        case VK_NUMPAD4:
            return key::numpad_4;
        case VK_NUMPAD5:
            return key::numpad_5;
        case VK_NUMPAD6:
            return key::numpad_6;
        case VK_NUMPAD7:
            return key::numpad_7;
        case VK_NUMPAD8:
            return key::numpad_8;
        case VK_NUMPAD9:
            return key::numpad_9;
        case 0x41:
            return key::a;
        case 0x42:
            return key::b;
        case 0x43:
            return key::c;
        case 0x44:
            return key::d;
        case 0x45:
            return key::e;
        case 0x46:
            return key::f;
        case 0x47:
            return key::g;
        case 0x48:
            return key::h;
        case 0x49:
            return key::i;
        case 0x4A:
            return key::j;
        case 0x4B:
            return key::k;
        case 0x4C:
            return key::l;
        case 0x4D:
            return key::m;
        case 0x4E:
            return key::n;
        case 0x4F:
            return key::o;
        case 0x50:
            return key::p;
        case 0x51:
            return key::q;
        case 0x52:
            return key::r;
        case 0x53:
            return key::s;
        case 0x54:
            return key::t;
        case 0x55:
            return key::u;
        case 0x56:
            return key::v;
        case 0x57:
            return key::w;
        case 0x58:
            return key::x;
        case 0x59:
            return key::y;
        case 0x5A:
            return key::z;
        case VK_SPACE:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

HWND
as_hwnd (
    void* window_handle
)
noexcept
{
    return static_cast<HWND>(window_handle);
} // function -----------------------------------------------------------------

int
to_dotval (
    int pixval,
    UINT dpi,
    int baseline
)
noexcept
{
    return MulDiv(pixval, dpi, baseline);
} // function -----------------------------------------------------------------

int
to_pixval (
    int dotval,
    UINT dpi,
    int baseline
)
noexcept
{
    return MulDiv(dotval, baseline, dpi);
} // function -----------------------------------------------------------------

void
forward_key_down_event_to_window (
    HWND window_handle,
    WPARAM w_param
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == window_handle) {
            key_event ev{
                key_event_type::key_down,
                translate_key_code(w_param)
            };
            current_association.second->handle_key_down_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_key_up_event_to_window (
    HWND window_handle,
    WPARAM w_param
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == window_handle) {
            key_event ev{
                key_event_type::key_up,
                translate_key_code(w_param)
            };
            current_association.second->handle_key_up_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    void* window_handle
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == as_hwnd(window_handle)) {
            current_association.second->update_root_layout();
            current_association.second->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

bool
forward_close_event_to_window (
    HWND window_handle
) {
    auto& window_associations{
        app()->grab_native_handle().window_associations
    };
    for (
        auto current_association{std::begin(window_associations)};
        current_association != std::end(window_associations);
        ++current_association
    ) {
        if (current_association->first == window_handle) {
            close_event ev{true};
            current_association->second->handle_close_event(ev);
            if (ev.should_close()) {
                window_associations.erase(current_association);
                return true;
            } else {
                return false;
            }
        }
    }
} // function -----------------------------------------------------------------

void
close_window (
    HWND window_handle
) {
    if (forward_close_event_to_window(window_handle)) {
        DestroyWindow(window_handle);
    }
} // function -----------------------------------------------------------------

widget*
find_widget (
    HWND widget_handle,
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
forward_command_event_to_widget (
    HWND widget_handle
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
    HWND widget_handle
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
    HWND widget_handle
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
    if (graphics_box_ptr) {
        graphics_box_ptr->render();
    }
} // function -----------------------------------------------------------------

LRESULT CALLBACK
window_procedure (
    HWND window_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
) {
    switch (message) {
        case WM_CLOSE: {
            close_window(window_handle);
            return 0;
        }
        case WM_KEYDOWN: {
            forward_key_down_event_to_window(window_handle, w_param);
            return 0;
        }
        case WM_KEYUP: {
            forward_key_up_event_to_window(window_handle, w_param);
            return 0;
        }
        case WM_SIZE: {
            LONG style{GetWindowLong(window_handle, GWL_STYLE)};
            if (style & WS_CHILD) {
                forward_resize_event_to_widget(window_handle);
            } else {
                forward_resize_event_to_window(window_handle);
            }
            return 0;
        }
        case WM_DPICHANGED: {
            // forward_dpi_update_to_window(window_handle, HIWORD(w_param));
            return 0;
        }
        case WM_CTLCOLORSTATIC: {
            WNDCLASSW window_class;
            GetClassInfoW(
                GetModuleHandleW(nullptr),
                window_class_name,
                &window_class
            );
            return reinterpret_cast<LRESULT>(window_class.hbrBackground);
        }
        case WM_COMMAND: {
            forward_command_event_to_widget(reinterpret_cast<HWND>(l_param));
            return 0;
        }
        default: {
            return DefWindowProcW(window_handle, message, w_param, l_param);
        }
    }
} // function -----------------------------------------------------------------

LRESULT CALLBACK
graphics_box_procedure (
    HWND window_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
) {
    switch (message) {
        case WM_SIZE: {
            forward_resize_event_to_widget(window_handle);
            return 0;
        }
        default: {
            return DefWindowProcW(window_handle, message, w_param, l_param);
        }
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

    std::wstring title_utf16{impl::to_wstring(initial_title)};

    RECT rectangle;
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = initial_width;
    rectangle.bottom = initial_height;

    AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, false);

    LONG window_width{rectangle.right - rectangle.left};
    LONG window_height{rectangle.bottom - rectangle.top};

    m_native_handle->window_handle = CreateWindowW(
        application_native_handle.window_class_name,
        title_utf16.data(),
        WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2,
        window_width,
        window_height,
        0,
        0,
        application_native_handle.application_instance_handle,
        0
    );
    m_native_handle->dpi = GetDpiForWindow(m_native_handle->window_handle);
    if (m_native_handle->dpi != 96) {
        window_width = impl::to_dotval(window_width, m_native_handle->dpi);
        window_height = impl::to_dotval(window_height, m_native_handle->dpi);
        SetWindowPos(
            m_native_handle->window_handle,
            nullptr,
            (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2,
            window_width,
            window_height,
            0
        );
    }

    if (!m_native_handle->window_handle) {
        throw std::runtime_error("Window creation failed.");
    }

    int native_modes[] = {
        SW_SHOWNORMAL,
        SW_SHOWMAXIMIZED,
        SW_SHOWMINIMIZED
    };
    m_native_handle->show_command
        = native_modes[static_cast<int>(initial_mode)];

    m_root_layout.m_enclosing_window_handle = m_native_handle;

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle->window_handle,
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
    auto dpi{GetDpiForWindow(m_native_handle->window_handle)};
    RECT rect;
    GetClientRect(m_native_handle->window_handle, &rect);
    width = impl::to_pixval(
        static_cast<int>(rect.right),
        dpi
    );
    height = impl::to_pixval(
        static_cast<int>(rect.bottom),
        dpi
    );
} // function -----------------------------------------------------------------

void
window::set_size (
    int new_width,
    int new_height
)
noexcept
{
    HWND window_handle{m_native_handle->window_handle};
    auto dpi{GetDpiForWindow(window_handle)};
    RECT rect{
        0,
        0,
        impl::to_dotval(new_width, dpi),
        impl::to_dotval(new_height, dpi)
    };
    DWORD style{
        static_cast<DWORD>(
            GetWindowLong(
                window_handle,
                GWL_STYLE
            )
        )
    };
    BOOL has_menu{GetMenu(window_handle) != nullptr};
    AdjustWindowRect(&rect, style, has_menu);
    SetWindowPos(
        window_handle,
        HWND_TOP,
        0,
        0,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_NOMOVE
    );
} // function -----------------------------------------------------------------

nux::string
window::get_title ()
const {
    std::wstring title_wstring;
    title_wstring.resize(GetWindowTextLengthW(m_native_handle->window_handle));
    GetWindowTextW(
        m_native_handle->window_handle,
        title_wstring.data(),
        static_cast<int>(title_wstring.size() + 1U)
    );
    return impl::to_nux_string(title_wstring);
} // function -----------------------------------------------------------------

void
window::set_title (
    nux::string_view new_title
) {
    std::wstring title_wstring{impl::to_wstring(new_title)};
    SetWindowTextW(m_native_handle->window_handle, title_wstring.data());
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
window::show ()
noexcept
{
    ShowWindow(
        m_native_handle->window_handle,
        m_native_handle->show_command
    );
    UpdateWindow(m_native_handle->window_handle);
    m_native_handle->show_command = SW_SHOWNORMAL;
} // function -----------------------------------------------------------------

void
window::hide ()
noexcept
{
    ShowWindow(m_native_handle->window_handle, SW_HIDE);
} // function -----------------------------------------------------------------

void
window::close ()
noexcept
{
    impl::close_window(m_native_handle->window_handle);
} // function -----------------------------------------------------------------

void
window::center ()
noexcept
{
    HWND window_handle{m_native_handle->window_handle};
    RECT rect_window;
    GetWindowRect(window_handle, &rect_window);
    LONG window_width{rect_window.right - rect_window.left};
    LONG window_height{rect_window.bottom - rect_window.top};

    HMONITOR monitor_handle{
        MonitorFromWindow(
            window_handle,
            MONITOR_DEFAULTTONEAREST
        )
    };
    MONITORINFO monitor_info;
    monitor_info.cbSize = sizeof (monitor_info);
    RECT rect_monitor;
    if (GetMonitorInfo(monitor_handle, &monitor_info)) {
        rect_monitor = monitor_info.rcWork;
    } else {
        rect_monitor.left = 0;
        rect_monitor.top = 0;
        rect_monitor.right = GetSystemMetrics(SM_CXSCREEN);
        rect_monitor.bottom = GetSystemMetrics(SM_CYSCREEN);
    }
    LONG monitor_width{rect_monitor.right - rect_monitor.left};
    LONG monitor_height{rect_monitor.bottom - rect_monitor.top};

    SetWindowPos(
        window_handle,
        HWND_TOP,
        rect_monitor.left + (monitor_width - window_width) / 2,
        rect_monitor.top  + (monitor_height - window_height) / 2,
        0,
        0,
        SWP_NOSIZE
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
