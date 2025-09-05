// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/application.hpp>

#include "windows.hpp"

namespace nux {

namespace impl {

LRESULT CALLBACK
window_procedure (
    HWND window_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
);

LRESULT CALLBACK
graphics_box_procedure (
    HWND window_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
);

} // namespace ----------------------------------------------------------------

constexpr const wchar_t* window_class_name{L"NuxWindow"};
constexpr const wchar_t* graphics_box_class_name{L"NuxGraphicsBox"};

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

    INITCOMMONCONTROLSEX init_common_controls_ex;
    init_common_controls_ex.dwSize = sizeof (INITCOMMONCONTROLSEX);
    init_common_controls_ex.dwICC = ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&init_common_controls_ex);

    m_native_handle->application_instance_handle = GetModuleHandleW(nullptr);
    m_native_handle->command_line = GetCommandLineW();
    m_native_handle->window_class_name = window_class_name;
    m_native_handle->graphics_box_class_name = graphics_box_class_name;

    WNDCLASSW window_class;
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = impl::window_procedure;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance
        = m_native_handle->application_instance_handle;
    window_class.hIcon = LoadIcon(0, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hbrBackground
        = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    window_class.lpszMenuName = 0;
    window_class.lpszClassName = m_native_handle->window_class_name;

    if (!RegisterClassW(&window_class)) {
        throw std::runtime_error{"Window class registration failed."};
    }

    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = impl::graphics_box_procedure;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance
        = m_native_handle->application_instance_handle;
    window_class.hIcon = LoadIcon(0, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hbrBackground
        = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    window_class.lpszMenuName = 0;
    window_class.lpszClassName = graphics_box_class_name;

    if (!RegisterClassW(&window_class)) {
        throw std::runtime_error{"Graphics box class registration failed."};
    }
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
    MSG message;
    ZeroMemory(&message, sizeof (MSG));
    m_is_running = true;
    while (!m_native_handle->window_associations.empty()) {
        if (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
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
