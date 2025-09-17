#include "edx11api.h"

namespace EProject
{
    void DX11GStates::setDefaultStates()
    {
        m_r_desc.FillMode = D3D11_FILL_SOLID;
        m_r_desc.CullMode = D3D11_CULL_BACK;
        m_r_desc.FrontCounterClockwise = true;
        m_r_desc.DepthBias = 0;
        m_r_desc.DepthBiasClamp = 0;
        m_r_desc.SlopeScaledDepthBias = 0;
        m_r_desc.DepthClipEnable = true;
        m_r_desc.ScissorEnable = false;
        m_r_desc.MultisampleEnable = false;
        m_r_desc.AntialiasedLineEnable = false;
        m_r_state = nullptr;

        m_stencil_ref = 0xff;
        m_d_desc.DepthEnable = false;
        m_d_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        m_d_desc.DepthFunc = D3D11_COMPARISON_LESS;
        m_d_desc.StencilEnable = false;
        m_d_desc.StencilReadMask = 0xff;
        m_d_desc.StencilWriteMask = 0xff;
        m_d_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        m_d_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        m_d_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        m_d_desc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER;
        m_d_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        m_d_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        m_d_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        m_d_desc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
        m_d_state = nullptr;

        m_b_desc.AlphaToCoverageEnable = false;
        m_b_desc.IndependentBlendEnable = true;

        for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
        {
            m_b_desc.RenderTarget[i].BlendEnable = false;
            m_b_desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
            m_b_desc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
            m_b_desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            m_b_desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
            m_b_desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
            m_b_desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            m_b_desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        }

        m_b_state = nullptr;
    }

    void DX11GStates::push()
    {
        m_states.emplace_back(this);
        m_r_state = nullptr;
        m_d_state = nullptr;
        m_b_state = nullptr;
    }

    void DX11GStates::pop()
    {
        const auto& last = m_states.back();

        m_r_desc = last.m_r_desc;
        m_d_desc = last.m_d_desc;
        m_b_desc = last.m_b_desc;
        m_r_state = last.m_r_state;
        m_d_state = last.m_d_state;
        m_b_state = last.m_b_state;
        m_stencil_ref = last.m_stencil_ref;

        if (m_r_state)
            m_deviceContext->RSSetState(m_r_state.Get());
        if (m_d_state)
            m_deviceContext->OMSetDepthStencilState(m_d_state.Get(), m_stencil_ref);
        if (m_b_state)
            m_deviceContext->OMSetBlendState(m_b_state.Get(), nullptr, 0xffffffff);
    }

    void DX11GStates::setWireframe(bool wire)
    {
        if ((m_r_desc.FillMode == D3D11_FILL_WIREFRAME) != wire)
        {
            m_r_desc.FillMode = wire ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
            m_r_state = nullptr;
        }
    }

    void DX11GStates::setCull(CullMode cm)
    {
        D3D11_CULL_MODE dx_cm = D3D11_CULL_NONE;
        switch (cm)
        {
        case CullMode::None: dx_cm = D3D11_CULL_NONE; break;
        case CullMode::Back: dx_cm = D3D11_CULL_BACK; break;
        case CullMode::Front: dx_cm = D3D11_CULL_FRONT; break;
        }

        if (m_r_desc.CullMode != dx_cm)
        {
            m_r_desc.CullMode = dx_cm;
            m_r_state = nullptr;
        }
    }

    void DX11GStates::setDepthEnable(bool enable)
    {
        if (static_cast<bool>(m_d_desc.DepthEnable) != enable)
        {
            m_d_desc.DepthEnable = enable;
            m_d_state = nullptr;
        }
    }

    void DX11GStates::setDepthWrite(bool enable)
    {
        if ((m_d_desc.DepthWriteMask == D3D11_DEPTH_WRITE_MASK_ALL) != enable)
        {
            m_d_desc.DepthWriteMask = enable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
            m_d_state = nullptr;
        }
    }

    void DX11GStates::setDepthFunc(Compare cmp)
    {
        D3D11_COMPARISON_FUNC dx_cmp = toDX(cmp);
        if (m_d_desc.DepthFunc != dx_cmp)
        {
            m_d_desc.DepthFunc = dx_cmp;
            m_d_state = nullptr;
        }
    }

    void DX11GStates::setBlend(bool enable, Blend src, Blend dst, int rt_index, BlendFunc bf)
    {
        setBlendSeparateAlpha(enable, src, dst, bf, src, dst, bf, rt_index);
    }

    void DX11GStates::setBlendSeparateAlpha(bool enable, Blend src_color, Blend dst_color, BlendFunc bf_color, Blend src_alpha, Blend dst_alpha, BlendFunc bf_alpha, int rt_index)
    {
        if (m_b_desc.IndependentBlendEnable != (rt_index >= 0))
        {
            m_b_desc.IndependentBlendEnable = (rt_index >= 0);
            m_b_state = nullptr;
        }

        D3D11_BLEND dx_src_blend = enable ? toDX(src_color) : D3D11_BLEND_ONE;
        D3D11_BLEND dx_dst_blend = enable ? toDX(dst_color) : D3D11_BLEND_ONE;
        D3D11_BLEND_OP dx_blend_op = enable ? toDX(bf_color) : D3D11_BLEND_OP_ADD;
        D3D11_BLEND dx_src_alpha_blend = enable ? toDX(src_alpha) : D3D11_BLEND_ONE;
        D3D11_BLEND dx_dst_alpha_blend = enable ? toDX(dst_alpha) : D3D11_BLEND_ONE;
        D3D11_BLEND_OP dx_blend_alpha_op = enable ? toDX(bf_alpha) : D3D11_BLEND_OP_ADD;

        int n = (rt_index < 0) ? 0 : rt_index;

        if (static_cast<bool>(m_b_desc.RenderTarget[n].BlendEnable) != enable)
        {
            m_b_desc.RenderTarget[n].BlendEnable = enable;
            m_b_state = nullptr;
        }

        if (m_b_desc.RenderTarget[n].SrcBlend != dx_src_blend)
        {
            m_b_desc.RenderTarget[n].SrcBlend = dx_src_blend;
            m_b_state = nullptr;
        }

        if (m_b_desc.RenderTarget[n].DestBlend != dx_dst_blend)
        {
            m_b_desc.RenderTarget[n].DestBlend = dx_dst_blend;
            m_b_state = nullptr;
        }

        if (m_b_desc.RenderTarget[n].BlendOp != dx_blend_op)
        {
            m_b_desc.RenderTarget[n].BlendOp = dx_blend_op;
            m_b_state = nullptr;
        }

        if (m_b_desc.RenderTarget[n].SrcBlendAlpha != dx_src_alpha_blend)
        {
            m_b_desc.RenderTarget[n].SrcBlendAlpha = dx_src_alpha_blend;
            m_b_state = nullptr;
        }

        if (m_b_desc.RenderTarget[n].DestBlendAlpha != dx_dst_alpha_blend)
        {
            m_b_desc.RenderTarget[n].DestBlendAlpha = dx_dst_alpha_blend;
            m_b_state = nullptr;
        }

        if (m_b_desc.RenderTarget[n].BlendOpAlpha != dx_blend_alpha_op)
        {
            m_b_desc.RenderTarget[n].BlendOpAlpha = dx_blend_alpha_op;
            m_b_state = nullptr;
        }

        if (rt_index < 0)
        {
            for (int i = 1; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
                m_b_desc.RenderTarget[i] = m_b_desc.RenderTarget[0];
        }
    }

    void DX11GStates::setColorWrite(bool enable, int rt_index)
    {
        if (m_b_desc.IndependentBlendEnable != (rt_index >= 0))
        {
            m_b_desc.IndependentBlendEnable = (rt_index >= 0);
            m_b_state = nullptr;
        }

        int n = (rt_index < 0) ? 0 : rt_index;
        if (static_cast<bool>(m_b_desc.RenderTarget[n].RenderTargetWriteMask) != enable)
        {
            m_b_desc.RenderTarget[n].RenderTargetWriteMask = enable ? D3D11_COLOR_WRITE_ENABLE_ALL : 0;
            m_b_state = nullptr;
        }

        if (rt_index < 0)
        {
            for (int i = 1; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
                m_b_desc.RenderTarget[i] = m_b_desc.RenderTarget[0];
        }
    }

    void DX11GStates::validateStates()
    {
        if (!m_r_state)
        {
            getD3DErr(m_device->CreateRasterizerState(&m_r_desc, &m_r_state));
            m_deviceContext->RSSetState(m_r_state.Get());
        }

        if (!m_d_state)
        {
            getD3DErr(m_device->CreateDepthStencilState(&m_d_desc, &m_d_state));
            m_deviceContext->OMSetDepthStencilState(m_d_state.Get(), m_stencil_ref);
        }

        if (!m_b_state)
        {
            getD3DErr(m_device->CreateBlendState(&m_b_desc, &m_b_state));
            m_deviceContext->OMSetBlendState(m_b_state.Get(), nullptr, 0xffffffff);
        }
    }

    DX11GStates::DX11GStates(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_device = device;
        m_deviceContext = device_context;
        setDefaultStates();
    }

    DX11GDevice::DX11GDevice()
    {

    }

    void DX11GDevice::init(const WindowParameters& params)
    {
        assert(params.size.x == 0);
        assert(params.size.y == 0);

        const auto& size = params.size;

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = size.x;
        sd.BufferDesc.Height = size.y;
        sd.BufferDesc.Format = params.isSrgb ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = params.hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        getD3DErr(D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            D3D11_CREATE_DEVICE_SINGLETHREADED,// | D3D11_CREATE_DEVICE_DEBUG,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &sd,
            &m_swapChain,
            &m_dev,
            nullptr,
            &m_context)
        );

        getD3DErr(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_backBuffer));
        getD3DErr(m_dev->CreateRenderTargetView(m_backBuffer.Get(), nullptr, &m_RTView));

        m_states = std::make_unique<DX11GStates>(m_dev.Get(), m_context.Get());

        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = size.x;
        descDepth.Height = size.y;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;

        getD3DErr(m_dev->CreateTexture2D(&descDepth, nullptr, &m_depthStencil));

        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = descDepth.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        getD3DErr(m_dev->CreateDepthStencilView(m_depthStencil.Get(), 0, &m_depthStencilView));
    }

    void DX11GDevice::shutdown()
    {

    }

    GDeviceAPI* DX11GDevice::getDevicePtr()
    {
        return static_cast<DX11GDevice*>(this);
    }

    GSamplerState* DX11GDevice::obtainSamplerState(const Sampler& s)
    {
        D3D11_SAMPLER_DESC desc = {};

        bool iscomparison = s.comparison != Compare::Never;

        if (s.anisotropy > 1)
        {
            desc.Filter = iscomparison ? D3D11_FILTER_COMPARISON_ANISOTROPIC : D3D11_FILTER_ANISOTROPIC;
        }
        else
        {
            if (iscomparison)
            {
                if (s.filter == TexFilter::Linear)
                {
                    if (s.mipfilter == TexFilter::Linear)
                    {
                        desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
                    }
                    else
                    {
                        desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
                    }
                }
                else
                {
                    if (s.mipfilter == TexFilter::Linear)
                    {
                        desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
                    }
                    else
                    {
                        desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
                    }
                }
            }
            else
            {
                if (s.filter == TexFilter::Linear)
                {
                    if (s.mipfilter == TexFilter::Linear)
                    {
                        desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                    }
                    else
                    {
                        desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
                    }
                }
                else
                {
                    if (s.mipfilter == TexFilter::Linear)
                    {
                        desc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
                    }
                    else
                    {
                        desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
                    }
                }
            }
        }

        desc.AddressU = toDX(s.wrap_x);
        desc.AddressV = toDX(s.wrap_x);
        desc.AddressW = toDX(s.wrap_x);
        desc.MipLODBias = 0;
        desc.MaxAnisotropy = s.anisotropy;
        desc.ComparisonFunc = toDX(s.comparison);
        desc.BorderColor[0] = s.border.x;
        desc.BorderColor[1] = s.border.y;
        desc.BorderColor[2] = s.border.z;
        desc.BorderColor[3] = s.border.w;
        desc.MinLOD = 0;
        desc.MaxLOD = s.mipfilter == TexFilter::None ? 0 : D3D11_FLOAT32_MAX;

        ComPtr<ID3D11SamplerState> sampler;
        getD3DErr(m_dev->CreateSamplerState(&desc, &sampler));
        m_samplers.insert({ s, sampler });

        //fix this
        return new DX11GSamplerState(sampler);
        //return new GSamplerState();
    }

    DX11GSamplerState::DX11GSamplerState(ComPtr<ID3D11SamplerState> ptr) : 
        m_state(ptr)
    {

    }

}