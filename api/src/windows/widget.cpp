// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/widget.hpp>

#include "windows.hpp"

namespace nux {

namespace impl {

LRESULT CALLBACK
control_procedure (
    HWND control_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param,
    UINT_PTR id_subclass,
    DWORD_PTR dw_ref_data
) {
    switch (message) {
    case WM_CLOSE:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SIZE:
    case WM_DPICHANGED:
    case WM_CTLCOLORSTATIC:
    case WM_COMMAND:
        return CallWindowProc(
            impl::window_procedure,
            control_handle,
            message,
            w_param,
            l_param
        );
    default:
        return DefSubclassProc(control_handle, message, w_param, l_param);
    }
} // function -----------------------------------------------------------------

widget_native_handle
create_widget (
    HWND parent_handle,
    native_widget_kind kind
)
noexcept
{
    std::wstring_view class_name;
    DWORD style;
    switch (kind) {
        case native_widget_kind::label:
            class_name = L"static";
            style = SS_CENTERIMAGE;
            break;
        case native_widget_kind::push_button:
            class_name = L"button";
            style = BS_PUSHBUTTON;
            break;
        case native_widget_kind::check_box:
            class_name = L"button";
            style = BS_AUTOCHECKBOX;
            break;
        case native_widget_kind::radio_button:
            class_name = L"button";
            style = BS_AUTORADIOBUTTON | WS_GROUP;
            break;
        case native_widget_kind::graphics_box:
            class_name = app()->grab_native_handle().graphics_box_class_name;
            style = 0;
            break;
        case native_widget_kind::group_box:
            class_name = L"button";
            style = BS_GROUPBOX;
            break;
    }
    auto parent_dpi{GetDpiForWindow(parent_handle)};
    HWND result{
        CreateWindowW(
            class_name.data(),
            L"",
            style | WS_CHILD | WS_TABSTOP,
            0,
            0,
            to_dotval(
                100,
                parent_dpi
            ),
            to_dotval(
                25,
                parent_dpi
            ),
            parent_handle,
            nullptr,
            app()->grab_native_handle().application_instance_handle,
            nullptr
        )
    };
    if (kind == native_widget_kind::group_box) {
        // SetWindowSubclass(result, impl::control_procedure, 0, 0);
    }
    auto font{GetStockObject(DEFAULT_GUI_FONT)};
    LOGFONTW logfont;
    GetObject(font, sizeof (LOGFONTW), &logfont);
    logfont.lfHeight
        = -12 * static_cast<double>(GetDpiForWindow(parent_handle)) / 96;
    auto new_font{CreateFontIndirectW(&logfont)};
    SendMessage(
        result,
        WM_SETFONT,
        reinterpret_cast<LPARAM>(new_font),
        true
    );
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
              enclosing_layout.grab_enclosing_window_handle().window_handle,
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
    RECT rect;
    GetWindowRect(m_native_handle->widget_handle, &rect);
    POINT point;
    point.x = rect.left;
    point.y = rect.top;
    ScreenToClient(m_native_handle->parent_handle, &point);
    auto dpi{get_parent_dpi()};
    x = impl::to_pixval(static_cast<int>(point.x), dpi);
    y = impl::to_pixval(static_cast<int>(point.y), dpi);
} // function -----------------------------------------------------------------

void
widget::get_size (
    int& width,
    int& height
)
const noexcept
{
    RECT rect;
    GetWindowRect(m_native_handle->widget_handle, &rect);
    auto dpi{get_parent_dpi()};
    width = impl::to_pixval(static_cast<int>(rect.right - rect.left), dpi);
    height = impl::to_pixval(static_cast<int>(rect.bottom - rect.top), dpi);
} // function -----------------------------------------------------------------

bool
widget::is_enabled ()
const noexcept
{
    return IsWindowEnabled(grab_native_handle().widget_handle);
} // function -----------------------------------------------------------------

void
widget::set_enabled (
    bool new_enabled
)
noexcept
{
    EnableWindow(grab_native_handle().widget_handle, new_enabled);
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    ShowWindow(m_native_handle->widget_handle, SW_SHOW);
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    ShowWindow(m_native_handle->widget_handle, SW_HIDE);
} // function -----------------------------------------------------------------

void
widget::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
    /*
        Here we update the font size.
    */
    auto font{
        reinterpret_cast<HFONT>(
            SendMessage(m_native_handle->widget_handle, WM_GETFONT, 0, 0)
        )
    };
    LOGFONTW logfont;
    GetObject(font, sizeof (LOGFONTW), &logfont);
    logfont.lfHeight = -12 * new_dpi / 96;
    auto new_font{CreateFontIndirectW(&logfont)};
    SendMessageW(
        m_native_handle->widget_handle,
        WM_SETFONT,
        (WPARAM)new_font,
        TRUE
    );

    /*
        Here we update the widget's position and size.
    */
    RECT rect;
    GetWindowRect(m_native_handle->widget_handle, &rect);
    POINT top_left;
    top_left.x = rect.left;
    top_left.y = rect.top;
    ScreenToClient(m_native_handle->parent_handle, &top_left);
    auto x{top_left.x};
    auto y{top_left.y};
    auto width{rect.right - rect.left};
    auto height{rect.bottom - rect.top};
    double factor{static_cast<double>(new_dpi) / old_dpi};
    SetWindowPos(
        m_native_handle->widget_handle,
        HWND_TOP,
        std::ceil(x * factor),
        std::ceil(y * factor),
        std::ceil(width * factor),
        std::ceil(height * factor),
        0
    );
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
widget::set_position_forcefully (
    int new_x,
    int new_y
)
noexcept
{
    auto dpi{get_parent_dpi()};
    SetWindowPos(
        m_native_handle->widget_handle,
        HWND_TOP,
        impl::to_dotval(new_x, dpi),
        impl::to_dotval(new_y, dpi),
        0,
        0,
        SWP_NOSIZE
    );
} // function -----------------------------------------------------------------

void
widget::set_size_forcefully (
    int new_width,
    int new_height
)
noexcept
{
    auto dpi{get_parent_dpi()};
    RECT rect;
    GetWindowRect(m_native_handle->widget_handle, &rect);
    SetWindowPos(
        m_native_handle->widget_handle,
        HWND_TOP,
        0,
        0,
        impl::to_dotval(new_width, dpi),
        impl::to_dotval(new_height, dpi),
        SWP_NOMOVE
    );
} // function -----------------------------------------------------------------

int
widget::get_parent_dpi ()
const noexcept
{
    return static_cast<int>(
        GetDpiForWindow(
            grab_enclosing_layout().grab_enclosing_window_handle()
                .window_handle
        )
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
