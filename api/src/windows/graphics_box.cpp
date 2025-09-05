// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

#include <nux/graphics_box.hpp>

#include "windows.hpp"

namespace nux {

namespace impl {

class alignas (16) constant_buffer_t {
public:
    // Public Data ------------------------------------------------------------

    matrix4x4<float> u_projection;
    paint_type u_paint_type;
    float u_opacity;
    float u_proj_min;
    float u_proj_max;
    gvector4d<float> u_color;
    gvector2d<float> u_gradient_start;
    gvector2d<float> u_gradient_end;
    int u_gradient_color_count;
    std::uint32_t padding1, padding2, padding3;
    gvector4d<float> u_gradient_colors[8];
    float u_gradient_stops[8];
}; // class -------------------------------------------------------------------

HRESULT
compile_shader (
    const std::string& source,
    const std::string& entryPoint,
    const std::string& profile,
    ID3DBlob** ppShaderBlob
) {
    if (!ppShaderBlob) {
        return E_INVALIDARG;
    }

    *ppShaderBlob = nullptr;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    flags |= D3DCOMPILE_DEBUG;
    flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* errorBlob{nullptr};

    HRESULT hr{
        D3DCompile(
            source.c_str(),     // pSrcData
            source.length(),    // SrcDataSize
            nullptr,            // pSourceName (optional)
            nullptr,            // pDefines (optional)
            nullptr,            // pInclude (optional)
            entryPoint.c_str(), // pEntrypoint
            profile.c_str(),    // pTarget
            flags,              // Flags1
            0,                  // Flags2
            ppShaderBlob,       // ppCode
            &errorBlob          // ppErrorMsgs
        )
    };

    if (FAILED(hr)) {
        if (errorBlob) {
            errorBlob->Release();
            throw std::runtime_error{"Shader compilation failed."};
        }
        return hr;
    }

    if (errorBlob) {
        errorBlob->Release();
    }

    return S_OK;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------- nux::graphics_box

// Constructors and Destructor ------------------------------------------------

graphics_box::graphics_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::graphics_box
          )
      }
{
    initialize();
} // function -----------------------------------------------------------------

graphics_box::graphics_box (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::graphics_box
          )
      }
{
    initialize();
} // function -----------------------------------------------------------------

graphics_box::~graphics_box ()
noexcept
{
    m_graphics_handle->swap_chain->SetFullscreenState(FALSE, NULL);

    m_graphics_handle->blend_state->Release();
    m_graphics_handle->input_layout->Release();
    m_graphics_handle->vertex_shader->Release();
    m_graphics_handle->pixel_shader->Release();
    m_graphics_handle->constant_buffer->Release();
    m_graphics_handle->swap_chain->Release();
    m_graphics_handle->back_buffer->Release();
    m_graphics_handle->device->Release();
    m_graphics_handle->device_context->Release();

    delete m_graphics_handle;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
graphics_box::clear (
    float red,
    float green,
    float blue,
    float alpha
) {
    const gvector4d<float> color{red, green, blue, alpha};
    m_graphics_handle->device_context->ClearRenderTargetView(
        m_graphics_handle->back_buffer,
        color.get_data_ptr()
    );
} // function -----------------------------------------------------------------

void
graphics_box::present ()
{
    m_graphics_handle->swap_chain->Present(0, 0);
} // function -----------------------------------------------------------------

void
graphics_box::render ()
{
    if (m_should_resize) {
        resize();
    }
    m_render_event_handler();
    present();
} // function -----------------------------------------------------------------

void
graphics_box::handle_resize_event ()
{
    m_should_resize = true;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
graphics_box::initialize ()
{
    m_graphics_handle = new graphics_native_handle;
    m_render_event_handler = impl::noop<>;

    m_should_resize = false;

    int width;
    int height;
    get_size(width, height);

    auto widget_handle{grab_native_handle().widget_handle};

    auto dpi{get_parent_dpi()};
    m_projection = matrix4x4<float>::build_orthographic(
        impl::to_dotval(width, dpi),
        impl::to_dotval(height, dpi)
    );

    DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
    ZeroMemory(&swap_chain_desc, sizeof (DXGI_SWAP_CHAIN_DESC));
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.Width = width;
    swap_chain_desc.BufferDesc.Height = height;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow = widget_handle;
    swap_chain_desc.SampleDesc.Count = 4;
    swap_chain_desc.Windowed = TRUE;
    swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (
        FAILED(
            D3D11CreateDeviceAndSwapChain(
                NULL,
                D3D_DRIVER_TYPE_HARDWARE,
                NULL,
                NULL,
                NULL,
                NULL,
                D3D11_SDK_VERSION,
                &swap_chain_desc,
                &m_graphics_handle->swap_chain,
                &m_graphics_handle->device,
                NULL,
                &m_graphics_handle->device_context
            )
        )
    ) {
        throw std::runtime_error{"Swap chain creation failed."};
    }

    SetWindowLong(
        widget_handle,
        GWL_EXSTYLE,
        GetWindowLong(widget_handle, GWL_EXSTYLE) | WS_EX_LAYERED
    );
    SetLayeredWindowAttributes(widget_handle, RGB(0, 0, 0), 255, LWA_COLORKEY);

    ID3D11Texture2D *back_buffer;
    m_graphics_handle->swap_chain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (LPVOID*)&back_buffer
    );

    if (
        FAILED(
            m_graphics_handle->device->CreateRenderTargetView(
                back_buffer,
                nullptr,
                &m_graphics_handle->back_buffer
            )
        )
    ) {
        throw std::runtime_error{"Render target view creation failed."};
    }
    back_buffer->Release();

    m_graphics_handle->device_context->OMSetRenderTargets(
        1,
        &m_graphics_handle->back_buffer,
        nullptr
    );

    // Configure the Viewport:

    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.Width = width;
    viewport.Height = height;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_graphics_handle->device_context->RSSetViewports(1, &viewport);

    // Configure Blending:

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));
    blend_desc.AlphaToCoverageEnable = FALSE;
    blend_desc.IndependentBlendEnable = FALSE;
    blend_desc.RenderTarget[0].BlendEnable = TRUE;
    blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].RenderTargetWriteMask
        = D3D11_COLOR_WRITE_ENABLE_ALL;

    if (
        FAILED(
            m_graphics_handle->device->CreateBlendState(
                &blend_desc,
                &m_graphics_handle->blend_state
            )
        )
    ) {
        throw std::runtime_error("Blend state creation failed.");
    }

    float blend_factor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    UINT sample_mask = 0xffffffff;
    m_graphics_handle->device_context->OMSetBlendState(
        m_graphics_handle->blend_state,
        blend_factor,
        sample_mask
    );

    // Configure Shaders:

    const std::string shader_source = R"hlsl(
cbuffer cb : register(b0) {
    row_major float4x4 u_projection;
    int u_paint_type;
    float u_opacity;
    float u_proj_min;
    float u_proj_max;
    float4 u_color;
    float2 u_gradient_start;
    float2 u_gradient_end;
    int u_gradient_color_count;
    uint padding1, padding2, padding3;
    float4 u_gradient_colors[8];
    float4 u_gradient_stops[2];
};

struct VOut {
    float4 position : SV_POSITION;
    float2 world_position : POSITION;
};

VOut VShader(float2 position : POSITION) {
    VOut output;

    output.position = mul(float4(position, 0.0f, 1.0f), u_projection);
    output.world_position = position;

    return output;
}

float getGradientStop(uint index) {
    uint division = index / 4;
    uint remainder = index % 4;
    switch (remainder) {
        case 0:
            return u_gradient_stops[division].x;
        case 1:
            return u_gradient_stops[division].y;
        case 2:
            return u_gradient_stops[division].z;
        default:
            return u_gradient_stops[division].w;
    }
}

float4 sampleGradient(float t) {
    float4 finalColor = u_gradient_colors[0];
    for (int i = 0; i < u_gradient_color_count - 1; ++i) {
        float currentStop = getGradientStop(i);
        float nextStop = getGradientStop(i + 1);
        if (t >= currentStop && t <= nextStop) {
            float segmentT = (t - currentStop) / (nextStop - currentStop);
            finalColor = lerp(u_gradient_colors[i], u_gradient_colors[i + 1], segmentT);
            break;
        }
    }
    if (t > getGradientStop(u_gradient_color_count - 1)) {
        finalColor = u_gradient_colors[u_gradient_color_count - 1];
    }
    return finalColor;
}

float4 sampleLinearGradient(float2 position) {
    float2 gradDir = u_gradient_end - u_gradient_start;
    float gradLength = length(gradDir);
    if (gradLength < 0.001) {
        return u_gradient_colors[0];
    }
    float2 gradNorm = gradDir / gradLength;
    float proj = dot(position - u_gradient_start, gradNorm);
    float t = clamp((proj - u_proj_min) / (u_proj_max - u_proj_min), 0.0, 1.0);
    return sampleGradient(t);
}

float4 sampleRadialGradient(float2 position) {
    if (u_gradient_color_count == 1) {
        return u_gradient_colors[0];
    }
    float distance = length(position - u_gradient_start);
    float gradientRadius = u_gradient_end.x;
    if (distance > gradientRadius) {
        return float4(0, 0, 0, 0);
    }
    float t = clamp(distance / gradientRadius, 0.0, 1.0);
    return sampleGradient(t);
}

float4 PShader(VOut v_out) : SV_TARGET {
    float4 color;
    switch (u_paint_type) {
        case 0:
            color = u_color;
            break;
        case 1:
            color = sampleLinearGradient(v_out.world_position);
            break;
        case 2:
            color = sampleRadialGradient(v_out.world_position);
            break;
    }
    return float4(color.r, color.g, color.b, color.a * u_opacity);
}
)hlsl";

    ID3D10Blob* VS;
    if (
        FAILED(
            impl::compile_shader(
                shader_source,
                "VShader",
                "vs_4_0",
                &VS
            )
        )
    ) {
        throw std::runtime_error{"Vertex shader compilation failed."};
    }

    ID3D10Blob* PS;
    if (
        FAILED(
            impl::compile_shader(
                shader_source,
                "PShader",
                "ps_4_0",
                &PS
            )
        )
    ) {
        throw std::runtime_error{"Pixel shader compilation failed."};
    }

    m_graphics_handle->device->CreateVertexShader(
        VS->GetBufferPointer(),
        VS->GetBufferSize(),
        NULL,
        &m_graphics_handle->vertex_shader
    );
    m_graphics_handle->device->CreatePixelShader(
        PS->GetBufferPointer(),
        PS->GetBufferSize(),
        NULL,
        &m_graphics_handle->pixel_shader
    );

    m_graphics_handle->device_context->VSSetShader(
        m_graphics_handle->vertex_shader,
        nullptr,
        0
    );
    m_graphics_handle->device_context->PSSetShader(
        m_graphics_handle->pixel_shader,
        nullptr,
        0
    );

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };

    m_graphics_handle->device->CreateInputLayout(
        ied,
        1,
        VS->GetBufferPointer(),
        VS->GetBufferSize(),
        &m_graphics_handle->input_layout
    );
    m_graphics_handle->device_context->IASetInputLayout(
        m_graphics_handle->input_layout
    );

    // Configure Buffers:

    D3D11_BUFFER_DESC cbd;
    cbd.ByteWidth = sizeof (impl::constant_buffer_t);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    cbd.StructureByteStride = 0;
    m_graphics_handle->device->CreateBuffer(
        &cbd,
        nullptr,
        &m_graphics_handle->constant_buffer
    );
} // function -----------------------------------------------------------------

void
graphics_box::resize ()
{
    int width;
    int height;
    get_size(width, height);

    auto dpi{get_parent_dpi()};
    m_projection = matrix4x4<float>::build_orthographic(
        impl::to_dotval(width, dpi),
        impl::to_dotval(height, dpi)
    );

    m_graphics_handle->device_context->OMSetRenderTargets(
        0,
        nullptr,
        nullptr
    );
    m_graphics_handle->back_buffer->Release();
    m_graphics_handle->swap_chain->ResizeBuffers(
        0,
        width,
        height,
        DXGI_FORMAT_UNKNOWN,
        0
    );

    ID3D11Texture2D* back_buffer;
    m_graphics_handle->swap_chain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**)&back_buffer
    );
    m_graphics_handle->device->CreateRenderTargetView(
        back_buffer,
        nullptr,
        &m_graphics_handle->back_buffer
    );
    back_buffer->Release();
    m_graphics_handle->device_context->OMSetRenderTargets(
        1,
        &m_graphics_handle->back_buffer,
        nullptr
    );

    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(
        impl::to_dotval(width, dpi)
    );
    viewport.Height = static_cast<float>(
        impl::to_dotval(height, dpi)
    );
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    m_graphics_handle->device_context->RSSetViewports(1, &viewport);

    m_should_resize = false;
} // function -----------------------------------------------------------------

void
graphics_box::render_path (
    const vector_path& path,
    const paint& render_paint,
    bool fill
) {
    if (path.grab_vertices().empty()) {
        return;
    }

    const impl::buffer& path_buffer{path.grab_buffer()};
    if (!path_buffer.is_ready()) {
        path_buffer.upload(*m_graphics_handle, path.grab_vertices());
    }
    UINT stride{sizeof (gvector2d<float>)};
    UINT offset{0};
    m_graphics_handle->device_context->IASetVertexBuffers(
        0,
        1,
        &(path_buffer.grab_native_handle().buffer),
        &stride,
        &offset
    );

    impl::constant_buffer_t constant_buffer;
    constant_buffer.u_projection = m_projection;
    constant_buffer.u_paint_type = render_paint.type;
    constant_buffer.u_color = render_paint.color;
    constant_buffer.u_opacity = render_paint.global_opacity;

    if (render_paint.type != paint_type::solid) {
        gvector2d<float> world_space_gradient_start{
            render_paint.gradient_start + path.grab_vertices().front()
        };
        gvector2d<float> world_space_gradient_end{
            render_paint.gradient_end + path.grab_vertices().front()
        };
        gvector2d<float> gradient_direction{
            world_space_gradient_end - world_space_gradient_start
        };
        gradient_direction.normalize();
        float minProj = (std::numeric_limits<float>::max)();
        float maxProj = std::numeric_limits<float>::lowest();
        for (const gvector2d<float>& current_vertex : path.grab_vertices()) {
            float proj{
                dot_product(
                    current_vertex - world_space_gradient_start,
                    gradient_direction
                )
            };
            minProj = (std::min)(minProj, proj);
            maxProj = (std::max)(maxProj, proj);
        }
        constant_buffer.u_proj_min = minProj;
        constant_buffer.u_proj_max = maxProj;
        if (render_paint.type == paint_type::radial_gradient) {
            constant_buffer.u_gradient_start = render_paint.gradient_start;
            constant_buffer.u_gradient_end = render_paint.gradient_end;
        } else {
            constant_buffer.u_gradient_start = world_space_gradient_start;
            constant_buffer.u_gradient_end = world_space_gradient_end;
        }

        std::vector<gvector4d<float>> colors;
        std::vector<float> stops;
        for (const auto& current_stop : render_paint.gradient_stops) {
            colors.push_back(current_stop.color);
            stops.push_back(current_stop.position);
        }
        std::copy(
            colors.begin(),
            colors.end(),
            std::begin(constant_buffer.u_gradient_colors)
        );
        std::copy(
            stops.begin(),
            stops.end(),
            std::begin(constant_buffer.u_gradient_stops)
        );
        constant_buffer.u_gradient_color_count = static_cast<int>(colors.size());
    }

    D3D11_MAPPED_SUBRESOURCE cb_ms;
    m_graphics_handle->device_context->Map(
        m_graphics_handle->constant_buffer,
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &cb_ms
    );
    memcpy(cb_ms.pData, &constant_buffer, sizeof (impl::constant_buffer_t));
    m_graphics_handle->device_context->Unmap(
        m_graphics_handle->constant_buffer,
        0
    );

    m_graphics_handle->device_context->VSSetConstantBuffers(
        0,
        1,
        &m_graphics_handle->constant_buffer
    );
    m_graphics_handle->device_context->PSSetConstantBuffers(
        0,
        1,
        &m_graphics_handle->constant_buffer
    );

    if (fill) {
        m_graphics_handle->device_context->IASetPrimitiveTopology(
            D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
        );
        m_graphics_handle->device_context->Draw(path_buffer.get_size(), 0);
    } else {
        m_graphics_handle->device_context->IASetPrimitiveTopology(
            D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
        );
        m_graphics_handle->device_context->Draw(path_buffer.get_size(), 0);
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
