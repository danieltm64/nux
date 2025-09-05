// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#ifndef NUX_WINDOWS_HPP_INCLUDED
#define NUX_WINDOWS_HPP_INCLUDED

#include <nux/string.hpp>
#include <nux/widget.hpp>

#include <vector>

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>

namespace nux {

class window;

class NUX_CONDITIONAL_EXPORT_CLASS application_native_handle {
public:
    // Public Data ------------------------------------------------------------

    HINSTANCE application_instance_handle;
    LPWSTR command_line;
    LPCWSTR window_class_name;
    LPCWSTR graphics_box_class_name;
    std::vector<std::pair<HWND, window*>> window_associations;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS window_native_handle {
public:
    // Public Data ------------------------------------------------------------

    int show_command;
    HWND window_handle;
    UINT dpi;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS layout_native_handle {
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS widget_native_handle {
public:
    // Public Data ------------------------------------------------------------

    HWND parent_handle;
    HWND widget_handle;
}; // class -------------------------------------------------------------------

class NUX_CONDITIONAL_EXPORT_CLASS graphics_native_handle {
public:
    // Public Data ------------------------------------------------------------

    IDXGISwapChain* swap_chain;
    ID3D11Device* device;
    ID3D11DeviceContext* device_context;
    ID3D11RenderTargetView* back_buffer;
    ID3D11BlendState* blend_state;
    ID3D11InputLayout* input_layout;
    ID3D11VertexShader* vertex_shader;
    ID3D11PixelShader* pixel_shader;
    ID3D11Buffer* constant_buffer;
}; // class -------------------------------------------------------------------

namespace impl {

class NUX_CONDITIONAL_EXPORT_CLASS buffer_native_handle {
public:
    // Public Data ------------------------------------------------------------

    ID3D11Buffer* buffer;
    std::size_t size;
}; // class -------------------------------------------------------------------

std::wstring
to_wstring (
    nux::string_view input
);

nux::string
to_nux_string (
    std::wstring_view input
);

widget_native_handle
create_widget (
    HWND parent_handle,
    native_widget_kind kind
)
noexcept;

int
to_dotval (
    int pixval,
    UINT dpi,
    int baseline = 96
)
noexcept;

int
to_pixval (
    int dotval,
    UINT dpi,
    int baseline = 96
)
noexcept;

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif
