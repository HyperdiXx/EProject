#include "edx11api.h"

#include <filesystem>

namespace EProject
{
    void getD3DErr(HRESULT hres) {
        switch (hres)
        {
        case(S_OK): return;
        case(S_FALSE): throw std::runtime_error("S_FALSE ");
        case(E_NOTIMPL): throw std::runtime_error("E_NOTIMPL");
        case(E_OUTOFMEMORY): throw std::runtime_error("E_OUTOFMEMORY");
        case(E_INVALIDARG): throw std::runtime_error("E_INVALIDARG");
        case(E_FAIL): throw std::runtime_error("E_FAIL");
        case(DXGI_ERROR_WAS_STILL_DRAWING): throw std::runtime_error("DXGI_ERROR_WAS_STILL_DRAWING");
        case(DXGI_ERROR_INVALID_CALL): throw std::runtime_error("DXGI_ERROR_INVALID_CALL ");
        case(D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD): throw std::runtime_error("D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD");
        case(D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS): throw std::runtime_error("D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS");
        case(D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS): throw std::runtime_error("D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS");
        case(D3D11_ERROR_FILE_NOT_FOUND): throw std::runtime_error("D3D11_ERROR_FILE_NOT_FOUND");
        case(DXGI_ERROR_ACCESS_DENIED): throw std::runtime_error("DXGI_ERROR_ACCESS_DENIED");
        case(DXGI_ERROR_ACCESS_LOST): throw std::runtime_error("DXGI_ERROR_ACCESS_LOST");
        case(DXGI_ERROR_ALREADY_EXISTS): throw std::runtime_error("DXGI_ERROR_ALREADY_EXISTS");
        case(DXGI_ERROR_CANNOT_PROTECT_CONTENT): throw std::runtime_error("DXGI_ERROR_CANNOT_PROTECT_CONTENT");
        case(DXGI_ERROR_DEVICE_HUNG): throw std::runtime_error("DXGI_ERROR_DEVICE_HUNG");
        case(DXGI_ERROR_DEVICE_REMOVED): throw std::runtime_error("DXGI_ERROR_DEVICE_REMOVED");
        case(DXGI_ERROR_DEVICE_RESET): throw std::runtime_error("DXGI_ERROR_DEVICE_RESET");
        case(DXGI_ERROR_DRIVER_INTERNAL_ERROR): throw std::runtime_error("DXGI_ERROR_DRIVER_INTERNAL_ERROR");
        case(DXGI_ERROR_FRAME_STATISTICS_DISJOINT): throw std::runtime_error("DXGI_ERROR_FRAME_STATISTICS_DISJOINT");
        case(DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE): throw std::runtime_error("DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE");
        case(DXGI_ERROR_MORE_DATA): throw std::runtime_error("DXGI_ERROR_MORE_DATA");
        case(DXGI_ERROR_NAME_ALREADY_EXISTS): throw std::runtime_error("DXGI_ERROR_NAME_ALREADY_EXISTS");
        case(DXGI_ERROR_NONEXCLUSIVE): throw std::runtime_error("DXGI_ERROR_NONEXCLUSIVE");
        case(DXGI_ERROR_NOT_CURRENTLY_AVAILABLE): throw std::runtime_error("DXGI_ERROR_NOT_CURRENTLY_AVAILABLE");
        case(DXGI_ERROR_NOT_FOUND): throw std::runtime_error("DXGI_ERROR_NOT_FOUND");
        case(DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED): throw std::runtime_error("DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED");
        case(DXGI_ERROR_REMOTE_OUTOFMEMORY): throw std::runtime_error("DXGI_ERROR_REMOTE_OUTOFMEMORY");
        case(DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE): throw std::runtime_error("DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE");
        case(DXGI_ERROR_SDK_COMPONENT_MISSING): throw std::runtime_error("DXGI_ERROR_SDK_COMPONENT_MISSING");
        case(DXGI_ERROR_SESSION_DISCONNECTED): throw std::runtime_error("DXGI_ERROR_SESSION_DISCONNECTED");
        case(DXGI_ERROR_UNSUPPORTED): throw std::runtime_error("DXGI_ERROR_UNSUPPORTED");
        case(DXGI_ERROR_WAIT_TIMEOUT): throw std::runtime_error("DXGI_ERROR_WAIT_TIMEOUT");
        default:
            auto s = std::to_string(hres);
            throw std::runtime_error(s.c_str());
        }
    }

    DXGI_FORMAT toDXGI_Fmt(TextureFmt fmt)
    {
        switch (fmt)
        {
        case TextureFmt::R8: return DXGI_FORMAT_R8_UNORM;
        case TextureFmt::RG8: return DXGI_FORMAT_R8G8_UNORM;
        case TextureFmt::RGBA8: return DXGI_FORMAT_R8G8B8A8_UNORM;
        case TextureFmt::RGBA8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        case TextureFmt::R16: return DXGI_FORMAT_R16_UNORM;
        case TextureFmt::RG16: return DXGI_FORMAT_R16G16_UNORM;
        case TextureFmt::RGBA16: return DXGI_FORMAT_R16G16B16A16_UNORM;
        case TextureFmt::R16f: return DXGI_FORMAT_R16_FLOAT;
        case TextureFmt::RG16f: return DXGI_FORMAT_R16G16_FLOAT;
        case TextureFmt::RGBA16f: return DXGI_FORMAT_R16G16B16A16_FLOAT;
        case TextureFmt::R32: return DXGI_FORMAT_R32_UINT;
        case TextureFmt::RG32: return DXGI_FORMAT_R32G32_UINT;
        case TextureFmt::RGB32: return DXGI_FORMAT_R32G32B32_UINT;
        case TextureFmt::RGBA32: return DXGI_FORMAT_R32G32B32A32_UINT;
        case TextureFmt::R32f: return DXGI_FORMAT_R32_FLOAT;
        case TextureFmt::RG32f: return DXGI_FORMAT_R32G32_FLOAT;
        case TextureFmt::RGB32f: return DXGI_FORMAT_R32G32B32_FLOAT;
        case TextureFmt::RGBA32f: return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case TextureFmt::D16: return DXGI_FORMAT_R16_UNORM;
        case TextureFmt::D24_S8: return DXGI_FORMAT_D24_UNORM_S8_UINT;
        case TextureFmt::D32f: return DXGI_FORMAT_R32_TYPELESS;
        case TextureFmt::D32f_S8: return DXGI_FORMAT_R32G8X24_TYPELESS;
        default:
            return DXGI_FORMAT_UNKNOWN;
        }
    }

    DXGI_FORMAT toDXGI_SRVFmt(TextureFmt fmt)
    {
        switch (fmt)
        {
        case TextureFmt::R8: return DXGI_FORMAT_R8_UNORM;
        case TextureFmt::RG8: return DXGI_FORMAT_R8G8_UNORM;
        case TextureFmt::RGBA8: return DXGI_FORMAT_R8G8B8A8_UNORM;
        case TextureFmt::RGBA8_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        case TextureFmt::R16: return DXGI_FORMAT_R16_UNORM;
        case TextureFmt::RG16: return DXGI_FORMAT_R16G16_UNORM;
        case TextureFmt::RGBA16: return DXGI_FORMAT_R16G16B16A16_UNORM;
        case TextureFmt::R16f: return DXGI_FORMAT_R16_FLOAT;
        case TextureFmt::RG16f: return DXGI_FORMAT_R16G16_FLOAT;
        case TextureFmt::RGBA16f: return DXGI_FORMAT_R16G16B16A16_FLOAT;
        case TextureFmt::R32: return DXGI_FORMAT_R32_UINT;
        case TextureFmt::RG32: return DXGI_FORMAT_R32G32_UINT;
        case TextureFmt::RGB32: return DXGI_FORMAT_R32G32B32_UINT;
        case TextureFmt::RGBA32: return DXGI_FORMAT_R32G32B32A32_UINT;
        case TextureFmt::R32f: return DXGI_FORMAT_R32_FLOAT;
        case TextureFmt::RG32f: return DXGI_FORMAT_R32G32_FLOAT;
        case TextureFmt::RGB32f: return DXGI_FORMAT_R32G32B32_FLOAT;
        case TextureFmt::RGBA32f: return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case TextureFmt::D16: return DXGI_FORMAT_R16_UNORM;
        case TextureFmt::D24_S8: return DXGI_FORMAT_D24_UNORM_S8_UINT;
        case TextureFmt::D32f: return DXGI_FORMAT_R32_FLOAT;
        case TextureFmt::D32f_S8: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
        default:
            return DXGI_FORMAT_UNKNOWN;
        }
    }

    D3D11_BLEND toDX(Blend b) {
        switch (b)
        {
        case Blend::Zero: return D3D11_BLEND_ZERO;
        case Blend::One: return D3D11_BLEND_ONE;
        case Blend::Src_Alpha: return D3D11_BLEND_SRC_ALPHA;
        case Blend::Inv_Src_Alpha: return D3D11_BLEND_INV_SRC_ALPHA;
        case Blend::Dst_Alpha: return D3D11_BLEND_DEST_ALPHA;
        case Blend::Inv_Dst_Alpha: return D3D11_BLEND_INV_DEST_ALPHA;
        case Blend::Src_Color: return D3D11_BLEND_SRC_COLOR;
        case Blend::Inv_Src_Color: return D3D11_BLEND_INV_SRC_COLOR;
        case Blend::Dst_Color: return D3D11_BLEND_DEST_COLOR;
        case Blend::Inv_Dst_Color: return D3D11_BLEND_INV_DEST_COLOR;
        default:
            return D3D11_BLEND_ZERO;
        }
    }

    D3D11_BLEND_OP toDX(BlendFunc b)
    {
        switch (b)
        {
        case BlendFunc::Add: return D3D11_BLEND_OP_ADD;
        case BlendFunc::Sub: return D3D11_BLEND_OP_SUBTRACT;
        case BlendFunc::Rev_Sub: return D3D11_BLEND_OP_REV_SUBTRACT;
        case BlendFunc::Min: return D3D11_BLEND_OP_MIN;
        case BlendFunc::Max: return D3D11_BLEND_OP_MAX;
        default:
            return D3D11_BLEND_OP_ADD;
        }
    }

    D3D11_COMPARISON_FUNC toDX(Compare cmp)
    {
        D3D11_COMPARISON_FUNC res = D3D11_COMPARISON_NEVER;

        switch (cmp)
        {
        case Compare::Never: res = D3D11_COMPARISON_NEVER; break;
        case Compare::Less: res = D3D11_COMPARISON_LESS; break;
        case Compare::Equal: res = D3D11_COMPARISON_EQUAL; break;
        case Compare::Less_Equal: res = D3D11_COMPARISON_LESS_EQUAL; break;
        case Compare::Greater: res = D3D11_COMPARISON_GREATER; break;
        case Compare::Not_Equal: res = D3D11_COMPARISON_NOT_EQUAL; break;
        case Compare::Greater_Equal: res = D3D11_COMPARISON_GREATER_EQUAL; break;
        case Compare::Always: res = D3D11_COMPARISON_ALWAYS; break;
        }

        return res;
    }

    D3D11_TEXTURE_ADDRESS_MODE toDX(TexWrap wrap)
    {
        D3D11_TEXTURE_ADDRESS_MODE res = D3D11_TEXTURE_ADDRESS_WRAP;
        switch (wrap)
        {
        case TexWrap::Repeat: res = D3D11_TEXTURE_ADDRESS_WRAP; break;
        case TexWrap::Mirror: res = D3D11_TEXTURE_ADDRESS_MIRROR; break;
        case TexWrap::Clamp: res = D3D11_TEXTURE_ADDRESS_CLAMP; break;
        case TexWrap::ClampBorder: res = D3D11_TEXTURE_ADDRESS_BORDER; break;
        }
        return res;
    }

    DXGI_FORMAT ConvertToDX(const LayoutField& l)
    {
        assert((l.num_fields > 0) && (l.num_fields < 5));
        switch (l.type) {
        case LayoutType::Byte:
        {
            switch (l.num_fields)
            {
            case 1: return l.do_norm ? DXGI_FORMAT_R8_UNORM : DXGI_FORMAT_R8_UINT;
            case 2: return l.do_norm ? DXGI_FORMAT_R8G8_UNORM : DXGI_FORMAT_R8G8_UINT;
            case 3: return DXGI_FORMAT_UNKNOWN;
            case 4: return l.do_norm ? DXGI_FORMAT_R8G8B8A8_UNORM : DXGI_FORMAT_R8G8B8A8_UINT;
            }
        }
        case LayoutType::Word:
        {
            switch (l.num_fields)
            {
            case 1: return l.do_norm ? DXGI_FORMAT_R16_UNORM : DXGI_FORMAT_R16_UINT;
            case 2: return l.do_norm ? DXGI_FORMAT_R16G16_UNORM : DXGI_FORMAT_R16G16_UINT;
            case 3: return DXGI_FORMAT_UNKNOWN;
            case 4: return l.do_norm ? DXGI_FORMAT_R16G16B16A16_UNORM : DXGI_FORMAT_R16G16B16A16_UINT;
            }
        }
        case LayoutType::UInt:
        {
            switch (l.num_fields)
            {
            case 1: return DXGI_FORMAT_R32_UINT;
            case 2: return DXGI_FORMAT_R32G32_UINT;
            case 3: return DXGI_FORMAT_R32G32B32_UINT;
            case 4: return DXGI_FORMAT_R32G32B32A32_UINT;
            }
        }
        case LayoutType::Float:
        {
            switch (l.num_fields)
            {
            case 1: return DXGI_FORMAT_R32_FLOAT;
            case 2: return DXGI_FORMAT_R32G32_FLOAT;
            case 3: return DXGI_FORMAT_R32G32B32_FLOAT;
            case 4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
            }
        }
        default:
            throw std::runtime_error("Unsupported format");
        }
    }

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

    DX11GStates::DX11GStates(ID3D11Device* device, ID3D11DeviceContext* device_context) : GStates()
    {
        m_device = device;
        m_deviceContext = device_context;
        setDefaultStates();
    }

    DX11GDevice::DX11GDevice(const GDevicePtr& device) : m_devicePtr(device)
    {
    }

    void DX11GDevice::init(const WindowParameters& params)
    {
        const auto& size = params.size;
     
        assert(size.x != 0);
        assert(size.y != 0);

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
            D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG,
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
        getD3DErr(m_backBuffer->Release());
        getD3DErr(m_RTView->Release());
        getD3DErr(m_depthStencil->Release());
        getD3DErr(m_depthStencilView->Release());
        getD3DErr(m_context->Release());
        getD3DErr(m_dev->Release());
    }

    FrameBufferPtr DX11GDevice::createFramebuffer()
    {
        return std::make_shared<DX11GFramebuffer>(m_devicePtr);
    }

    GPUTexture2DPtr DX11GDevice::createTexture2D()
    {
        return std::make_shared<DX11GPUTexture2D>(m_devicePtr);
    }

    IndexBufferPtr DX11GDevice::createIndexBuffer()
    {
        return std::make_shared<DX11GIndexBuffer>(m_devicePtr);
    }

    VertexBufferPtr DX11GDevice::createVertexBuffer()
    {
        return std::make_shared<DX11GVertexBuffer>(m_devicePtr);
    } 

    ShaderProgramPtr DX11GDevice::createShaderProgram()
    {
        return std::make_shared<DX11GShaderProgram>(m_devicePtr);
    }

    UniformBufferPtr DX11GDevice::createUniformBuffer()
    {        
        return std::make_shared<DX11GUniformBuffer>(m_devicePtr);
    }

    StructuredBufferPtr DX11GDevice::createStructuredBuffer()
    {
        return std::make_shared<DX11GStructuredBuffer>(m_devicePtr);
    }

    void DX11GDevice::endFrame()
    {
        m_swapChain->Present(1, 0);
    }

    void DX11GDevice::draw(int vert_start, int vert_count, int instance_count, int base_instance)
    {
        if (instance_count)
        {
            m_context->DrawInstanced(vert_count, instance_count, vert_start, base_instance);
        }
        else
        {
            m_context->Draw(vert_count, vert_start);
        }
    }

    void DX11GDevice::drawIndexed(int index_start, int index_count, int instance_count, int base_vertex, int base_instance)
    {
        if (instance_count)
        {
            m_context->DrawIndexedInstanced(index_count, instance_count, index_start, base_vertex, base_instance);
        }
        else
        {
            m_context->DrawIndexed(index_count, index_start, base_vertex);
        }
    }

    bool DX11GDevice::createDefaultRTV(const WindowParameters& params)
    {
        ID3D11RenderTargetView* tmpRT = nullptr;
        ID3D11DepthStencilView* tmpDS = nullptr;
        m_context->OMSetRenderTargetsAndUnorderedAccessViews(1, &tmpRT, tmpDS, 0, 0, nullptr, nullptr);
        m_RTView = nullptr;
        m_backBuffer = nullptr;
        getD3DErr(m_swapChain->ResizeBuffers(1, params.size.x, params.size.y, params.isSrgb ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM, 0));
        getD3DErr(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_backBuffer));
        getD3DErr(m_dev->CreateRenderTargetView(m_backBuffer.Get(), nullptr, &m_RTView));
        getD3DErr(m_dev->CreateDepthStencilView(m_depthStencil.Get(), nullptr, &m_depthStencilView));
        return true;
    }

    void DX11GDevice::setDefaultFramebuffer()
    {
        ID3D11RenderTargetView* defRT = m_RTView.Get();
        ID3D11DepthStencilView* defDS = m_depthStencilView.Get();

        getDX11DeviceContext()->OMSetRenderTargetsAndUnorderedAccessViews(1, &defRT, defDS, 0, 0, nullptr, nullptr);
    }
    
    void DX11GDevice::setViewport(const glm::vec2& size)
    {
        D3D11_VIEWPORT vp = {};
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        vp.Width = size.x;
        vp.Height = size.y;
        vp.MinDepth = 0.0;
        vp.MaxDepth = 1.0;
        getDX11DeviceContext()->RSSetViewports(1, &vp);
    }

    void DX11GDevice::clearRenderTarget(const float* color, bool clearDepth)
    {
        m_context->ClearRenderTargetView(m_RTView.Get(), color);

        if (auto* dsView = m_depthStencilView.Get())
        {
            m_context->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        }
    }

    GDeviceAPI* DX11GDevice::getDevicePtrRaw()
    {
        return static_cast<DX11GDevice*>(this);
    }

    GSamplerState* DX11GDevice::obtainSamplerState(const Sampler& s)
    {
        D3D11_SAMPLER_DESC desc = {};

        const bool isComparison = s.comparison != Compare::Never;

        if (s.anisotropy > 1)
        {
            desc.Filter = isComparison ? D3D11_FILTER_COMPARISON_ANISOTROPIC : D3D11_FILTER_ANISOTROPIC;
        }
        else
        {
            if (isComparison)
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

        return new DX11GSamplerState(sampler);
    }

    GStates* DX11GDevice::getStates()
    {        
        return m_states.get();
    }

    ID3D11Device* DX11GDevice::getDX11Device() const
    {
        return m_dev.Get();
    }

    ID3D11DeviceContext* DX11GDevice::getDX11DeviceContext() const
    {
        return m_context.Get();
    }

    DX11GSamplerState::DX11GSamplerState(ComPtr<ID3D11SamplerState> ptr) :
        m_state(ptr)
    {

    }

    DX11GShaderProgram::DX11GShaderProgram(const GDevicePtr& device) : ShaderProgram(device)
    {

    }

    DX11GShaderProgram::~DX11GShaderProgram()
    {

    }

    void DX11GShaderProgram::DX11GShaderSlot::select(ID3D11DeviceContext* dev) const
    {
        ID3D11Buffer* b = buffer ? buffer.Get() : nullptr;
        ID3D11ShaderResourceView* v = view ? view.Get() : nullptr;

        if (bindPoints[int(ShaderType::Vertex)] >= 0)
        {
            switch (kind)
            {
                case SlotKind::Uniform: { dev->VSSetConstantBuffers(bindPoints[int(ShaderType::Vertex)], 1, &b); break; }
                case SlotKind::Texture: { dev->VSSetShaderResources(bindPoints[int(ShaderType::Vertex)], 1, &v); break; }
                case SlotKind::Buffer: { dev->VSSetShaderResources(bindPoints[int(ShaderType::Vertex)], 1, &v); break; }
                case SlotKind::Sampler: { dev->VSSetSamplers(bindPoints[int(ShaderType::Vertex)], 1, &sampler); break; }
            }
        }

        if (bindPoints[int(ShaderType::Hull)] >= 0)
        {
            switch (kind)
            {
                case SlotKind::Uniform: { dev->HSSetConstantBuffers(bindPoints[int(ShaderType::Hull)], 1, &b); break; }
                case SlotKind::Texture: { dev->HSSetShaderResources(bindPoints[int(ShaderType::Hull)], 1, &v); break; }
                case SlotKind::Buffer: { dev->HSSetShaderResources(bindPoints[int(ShaderType::Hull)], 1, &v); break; }
                case SlotKind::Sampler: { dev->HSSetSamplers(bindPoints[int(ShaderType::Hull)], 1, &sampler); break; }
            }
        }

        if (bindPoints[int(ShaderType::Domain)] >= 0)
        {
            switch (kind)
            {
                case SlotKind::Uniform: { dev->DSSetConstantBuffers(bindPoints[int(ShaderType::Domain)], 1, &b); break; }
                case SlotKind::Texture: { dev->DSSetShaderResources(bindPoints[int(ShaderType::Domain)], 1, &v); break; }
                case SlotKind::Buffer: { dev->DSSetShaderResources(bindPoints[int(ShaderType::Domain)], 1, &v); break; }
                case SlotKind::Sampler: { dev->DSSetSamplers(bindPoints[int(ShaderType::Domain)], 1, &sampler); break; }
            }
        }

        if (bindPoints[int(ShaderType::Geometry)] >= 0)
        {
            switch (kind)
            {
                case SlotKind::Uniform: { dev->GSSetConstantBuffers(bindPoints[int(ShaderType::Geometry)], 1, &b); break; }
                case SlotKind::Texture: { dev->GSSetShaderResources(bindPoints[int(ShaderType::Geometry)], 1, &v); break; }
                case SlotKind::Buffer: { dev->GSSetShaderResources(bindPoints[int(ShaderType::Geometry)], 1, &v); break; }
                case SlotKind::Sampler: { dev->GSSetSamplers(bindPoints[int(ShaderType::Geometry)], 1, &sampler); break; }
            }
        }

        if (bindPoints[int(ShaderType::Pixel)] >= 0)
        {
            switch (kind)
            {
                case SlotKind::Uniform: { dev->PSSetConstantBuffers(bindPoints[int(ShaderType::Pixel)], 1, &b); break; }
                case SlotKind::Texture: { dev->PSSetShaderResources(bindPoints[int(ShaderType::Pixel)], 1, &v); break; }
                case SlotKind::Buffer: { dev->PSSetShaderResources(bindPoints[int(ShaderType::Pixel)], 1, &v); break; }
                case SlotKind::Sampler: { dev->PSSetSamplers(bindPoints[int(ShaderType::Pixel)], 1, &sampler); break; }
            }
        }

        if (bindPoints[int(ShaderType::Compute)] >= 0)
        {
            switch (kind)
            {
                case SlotKind::Uniform: { dev->CSSetConstantBuffers(bindPoints[int(ShaderType::Compute)], 1, &b); break; }
                case SlotKind::Texture: { dev->CSSetShaderResources(bindPoints[int(ShaderType::Compute)], 1, &v); break; }
                case SlotKind::Buffer: { dev->CSSetShaderResources(bindPoints[int(ShaderType::Compute)], 1, &v); break; }
                case SlotKind::Sampler: { dev->CSSetSamplers(bindPoints[int(ShaderType::Compute)], 1, &sampler); break; }
            }
        }
    }

    bool DX11GShaderProgram::compileFromFile(const ShaderInput& input)
    {
        if (!std::filesystem::exists(input.filePath))
        {
            return false;
        }

        ID3DBlob* compiledShader = nullptr;
        ID3DBlob* errorMessages = nullptr;

        D3D_SHADER_MACRO defines[] =
        {
            "HLSL5", "1",
            "DISABLE_WAVE_INTRINSICS", "1",
            NULL, NULL
        };

        int flags = 0;

        const char* target = input.target.c_str();
        const char* entryPoint = input.entyPoint.c_str();

        HRESULT hr = (D3DCompileFromFile(input.filePath.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, target,
            flags, 0, &compiledShader, &errorMessages));

        if (FAILED(hr) && errorMessages)
        {
            const char* errorMsg = (const char*)errorMessages->GetBufferPointer();
            MessageBox(nullptr, (LPCWSTR)errorMsg, L"Shader Compilation Error", MB_RETRYCANCEL);
            return false;
        }

        m_shaderData[int(input.type)] = compiledShader;

        //m_blob = compiledShader;

        //else
        //{
        //    // Compress the shader
        //    D3D_SHADER_DATA shaderData;
        //    shaderData.pBytecode = compiledShader->GetBufferPointer();
        //    shaderData.BytecodeLength = compiledShader->GetBufferSize();
        //    ID3DBlobPtr compressedShader;
        //    DXCall(D3DCompressShaders(1, &shaderData, D3D_COMPRESS_SHADER_KEEP_ALL_PARTS, &compressedShader));

        //    // Create the cache directory if it doesn't exist
        //    if (DirectoryExists(baseCacheDir.c_str()) == false)
        //        Win32Call(CreateDirectory(baseCacheDir.c_str(), nullptr));

        //    if (DirectoryExists(cacheDir.c_str()) == false)
        //        Win32Call(CreateDirectory(cacheDir.c_str(), nullptr));

        //    File cacheFile(cacheName.c_str(), File::OpenWrite);

        //    // Write the compiled shader to disk
        //    uint64 shaderSize = compressedShader->GetBufferSize();
        //    cacheFile.Write(shaderSize, compressedShader->GetBufferPointer());

        //    return true;
        //}

        return true;
    }

    bool DX11GShaderProgram::create()
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        
        for (int i = 0; i < 6; ++i)
        {
            auto blob = m_shaderData[i];
            if (!blob)
            {
                continue;
            }

            //std::vector<char>& raw_data = m_shaderCode[int(st)];
            ShaderType st = cShaders[i];

            void* blobPtr = (ID3D10Blob**)blob->GetBufferPointer();
            size_t blobSize = blob->GetBufferSize();

            std::string shaderCode = {};
            shaderCode.append((char*)(blob->GetBufferPointer()), blob->GetBufferSize());

            auto& elem = m_shaderCode[i];
            elem = std::move(shaderCode);

            ID3D11DeviceChild** tmp = &m_shaders[int(st)];

            switch (cShaders[i])
            {
            case ShaderType::Vertex:
            {
                getD3DErr(dx11Device->getDX11Device()->CreateVertexShader(blobPtr, blobSize, nullptr, (ID3D11VertexShader**)tmp));
            } break;
            case ShaderType::Hull:
            {
                getD3DErr(dx11Device->getDX11Device()->CreateHullShader(blobPtr, blobSize, nullptr, (ID3D11HullShader**)tmp));
            } break;
            case ShaderType::Domain:
            {
                getD3DErr(dx11Device->getDX11Device()->CreateDomainShader(blobPtr, blobSize, nullptr, (ID3D11DomainShader**)tmp));
            } break;
            case ShaderType::Geometry:
            {
                getD3DErr(dx11Device->getDX11Device()->CreateGeometryShader(blobPtr, blobSize, nullptr, (ID3D11GeometryShader**)tmp));
            } break;
            case ShaderType::Pixel:
            {
                getD3DErr(dx11Device->getDX11Device()->CreatePixelShader(blobPtr, blobSize, nullptr, (ID3D11PixelShader**)tmp));
            } break;
            case ShaderType::Compute:
            {
                getD3DErr(dx11Device->getDX11Device()->CreateComputeShader(blobPtr, blobSize, nullptr, (ID3D11ComputeShader**)tmp));
            } break;
            }
            autoReflect(elem.data(), int(elem.size()), st);
        }

        return true;
    }

    void DX11GShaderProgram::selectShaderPrograms()
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        auto* context = dx11Device->getDX11DeviceContext();

        ID3D11DeviceChild* tmp = nullptr;
        tmp = m_shaders[int(ShaderType::Vertex)] ? m_shaders[int(ShaderType::Vertex)].Get() : nullptr;
        context->VSSetShader((ID3D11VertexShader*)tmp, nullptr, 0);
        tmp = m_shaders[int(ShaderType::Hull)] ? m_shaders[int(ShaderType::Hull)].Get() : nullptr;
        context->HSSetShader((ID3D11HullShader*)tmp, nullptr, 0);
        tmp = m_shaders[int(ShaderType::Domain)] ? m_shaders[int(ShaderType::Domain)].Get() : nullptr;
        context->DSSetShader((ID3D11DomainShader*)tmp, nullptr, 0);
        tmp = m_shaders[int(ShaderType::Geometry)] ? m_shaders[int(ShaderType::Geometry)].Get() : nullptr;
        context->GSSetShader((ID3D11GeometryShader*)tmp, nullptr, 0);
        tmp = m_shaders[int(ShaderType::Pixel)] ? m_shaders[int(ShaderType::Pixel)].Get() : nullptr;
        context->PSSetShader((ID3D11PixelShader*)tmp, nullptr, 0);
        tmp = m_shaders[int(ShaderType::Compute)] ? m_shaders[int(ShaderType::Compute)].Get() : nullptr;
        context->CSSetShader((ID3D11ComputeShader*)tmp, nullptr, 0);
    }

    void DX11GShaderProgram::setInputBuffers(const VertexBufferPtr& vbo, const IndexBufferPtr& ibo, const VertexBufferPtr& instances, int instanceStepRate)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
    }

    void DX11GShaderProgram::drawIndexed(PrimTopology pt, const DrawIndexedCmd& cmd)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
    }

    void DX11GShaderProgram::drawIndexed(PrimTopology pt, const std::vector<DrawIndexedCmd>& cmd_buf)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
    }

    void DX11GShaderProgram::drawIndexed(PrimTopology pt, int index_start, int index_count, int instance_count, int base_vertex, int base_instance)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
    }

    void DX11GShaderProgram::draw(PrimTopology pt, int vert_start, int vert_count, int instance_count, int base_instance)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
    }

    void DX11GShaderProgram::setValue(const char* name, float v)
    {
        ShaderProgram::setValue(name, v);
    }

    void DX11GShaderProgram::setValue(const char* name, int i)
    {
        ShaderProgram::setValue(name, i);
    }

    void DX11GShaderProgram::setValue(const char* name, const glm::vec2& v)
    {
        ShaderProgram::setValue(name, v);
    }

    void DX11GShaderProgram::setValue(const char* name, const glm::vec3& v)
    {
        ShaderProgram::setValue(name, v);
    }

    void DX11GShaderProgram::setValue(const char* name, const glm::vec4& v)
    {
        ShaderProgram::setValue(name, v);
    }

    void DX11GShaderProgram::setValue(const char* name, const glm::mat4& m)
    {
        ShaderProgram::setValue(name, m);
    }

    void DX11GShaderProgram::setResource(const char* name, const UniformBufferPtr& ubo)
    {
        int idx = findSlot(name);
        if (idx < 0)
        {
            return;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        auto* slot = static_cast<DX11GShaderSlot*>(m_slots[idx].get());
        auto dx11UBO = static_cast<DX11GUniformBuffer*>(ubo.get())->getHandle().Get();
        if ((slot->buffer ? slot->buffer.Get() : nullptr) != (ubo ? dx11UBO : nullptr))
        {
            slot->buffer = ubo ? dx11UBO : nullptr;
            if (isProgramActive())
            {                
                slot->select(dx11Device->getDX11DeviceContext());
            }
        }
    }

    void DX11GShaderProgram::setResource(const char* name, const StructuredBufferPtr& sbo)
    {
        int idx = findSlot(name);
        if (idx < 0)
        {
            return;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        auto* dx11Sbo = static_cast<DX11GStructuredBuffer*>(sbo.get());
        assert(dx11Sbo);

        auto* slot = static_cast<DX11GShaderSlot*>(m_slots[idx].get());
        ComPtr<ID3D11ShaderResourceView> srv = dx11Sbo ? dx11Sbo->getShaderResource() : nullptr;

        if ((slot->view ? slot->view.Get() : nullptr) != srv.Get())
        {
            slot->view = std::move(srv);
            if (isProgramActive())
            {
                slot->select(dx11Device->getDX11DeviceContext());
            }
        }
    }

    void DX11GShaderProgram::setResource(const char* name, const GPUTexture2DPtr& tex, bool as_array, bool as_cubemap)
    {
        int idx = findSlot(name);
        if (idx < 0)
        {
            return;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
    
        auto* dx11Texture2D = static_cast<DX11GPUTexture2D*>(tex.get());
        assert(dx11Texture2D);

        auto* slot = static_cast<DX11GShaderSlot*>(m_slots[idx].get());
        ComPtr<ID3D11ShaderResourceView> srv = dx11Texture2D ? dx11Texture2D->getShaderResource(as_array, as_cubemap) : nullptr;
        if ((slot->view ? slot->view.Get() : nullptr) != srv.Get())
        {
            slot->view = std::move(srv);
            if (isProgramActive())
            {
                slot->select(dx11Device->getDX11DeviceContext());
            }
        }
    }

    //????
    //void setResource(const char* name, const Texture3DPtr& tex);

    void DX11GShaderProgram::setResource(const char* name, const Sampler& s)
    {
        int idx = findSlot(name);
        if (idx < 0)
        {
            return;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        auto* slot = static_cast<DX11GShaderSlot*>(m_slots[idx].get());
        
        ID3D11SamplerState* newSamplerPtr = static_cast<DX11GSamplerState*>(dx11Device->obtainSamplerState(s))->getStatePtr().Get();
        if (slot->sampler != newSamplerPtr)
        {
            slot->sampler = newSamplerPtr;
            if (isProgramActive())
            {
                slot->select(dx11Device->getDX11DeviceContext());
            }
        }
    }
    
    const Layout* DX11GShaderProgram::autoReflectCB(ID3D11ShaderReflectionConstantBuffer* cb_ref)
    {
        D3D11_SHADER_BUFFER_DESC cb_desc;
        cb_ref->GetDesc(&cb_desc);
        assert(cb_desc.Type == D3D_CT_CBUFFER);

        std::vector<char> raw_data;
        raw_data.resize(cb_desc.Size);
        LayoutSelector* lb = getLayoutSelector();
        for (UINT vidx = 0; vidx < cb_desc.Variables; vidx++)
        {
            ID3D11ShaderReflectionVariable* var_ref;
            var_ref = cb_ref->GetVariableByIndex(vidx);
            D3D11_SHADER_VARIABLE_DESC var_desc;
            var_ref->GetDesc(&var_desc);

            ID3D11ShaderReflectionType* type_ref = var_ref->GetType();
            D3D11_SHADER_TYPE_DESC type_desc;
            type_ref->GetDesc(&type_desc);

            LayoutType lt = {};
            switch (type_desc.Type)
            {
            case D3D_SVT_INT: lt = LayoutType::UInt; break;
            case D3D_SVT_UINT: lt = LayoutType::UInt; break;
            case D3D_SVT_FLOAT: lt = LayoutType::Float; break;
            default:
                throw std::runtime_error("unsupported layout type");
            }

            int arr_size = type_desc.Elements == 0 ? 1 : type_desc.Elements;
            lb->add(var_desc.Name, lt, type_desc.Rows * type_desc.Columns, false, var_desc.StartOffset, arr_size);

            if (var_desc.DefaultValue)
            {
                memcpy(&raw_data[var_desc.StartOffset], var_desc.DefaultValue, var_desc.Size);
            }
        }
        return lb->end(cb_desc.Size);
    }

    void DX11GShaderProgram::autoReflect(const void* data, int data_size, ShaderType st)
    {
        ComPtr<ID3D11ShaderReflection> ref;
        D3DReflect(data, data_size, __uuidof(ID3D11ShaderReflection), &ref);
        D3D11_SHADER_DESC shader_desc = {};
        auto hr = ref->GetDesc(&shader_desc);

        for (UINT i = 0; i < shader_desc.BoundResources; i++)
        {
            D3D11_SHADER_INPUT_BIND_DESC res_desc;
            ref->GetResourceBindingDesc(i, &res_desc);

            SlotKind kind;
            switch (res_desc.Type)
            {
            case D3D_SIT_CBUFFER: kind = SlotKind::Uniform; break;
            case D3D_SIT_TEXTURE: kind = SlotKind::Texture; break;
            case D3D_SIT_STRUCTURED: kind = SlotKind::Buffer; break;
            case D3D_SIT_SAMPLER: kind = SlotKind::Sampler; break;
            default:
                throw std::runtime_error("Unsupported resource type!");
            }

            const Layout* l = res_desc.Type == D3D_SIT_CBUFFER ? autoReflectCB(ref->GetConstantBufferByName(res_desc.Name)) : nullptr;
            const int idx = obtainSlotIdx(kind, std::string(res_desc.Name), l);
            auto* slot = static_cast<DX11GShaderSlot*>(m_slots[idx].get());
            slot->bindPoints[int(st)] = res_desc.BindPoint;

            if (slot->name == "Globals")
            {
                auto ub = std::make_shared<DX11GUniformBuffer>(m_device);
                ub->setState(slot->layout, 1);                
                slot->buffer = ub->getHandle();

                m_ub[int(st)] = ub;
            }
        }
    }

    void DX11GShaderProgram::selectShaderSlots()
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device); 
        for (auto& slot : m_slots)
        {
            auto* slotPtr = static_cast<DX11GShaderSlot*>(slot.get());
            slotPtr->select(dx11Device->getDX11DeviceContext());
        }
    }

    void DX11GShaderProgram::selectInputBuffers()
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        auto* deviceContext = dx11Device->getDX11DeviceContext();

        ID3D11Buffer* dxBuf = m_selectedVBO ? static_cast<DX11GVertexBuffer*>(m_selectedVBO.get())->m_handle.Get() : nullptr;
        UINT stride = m_selectedVBO ? m_selectedVBO->getLayout()->stride : 0;
        UINT offset = 0;
        deviceContext->IASetVertexBuffers(0, 1, &dxBuf, &stride, &offset);

        dxBuf = m_selectedInstances ? static_cast<DX11GVertexBuffer*>(m_selectedInstances.get())->m_handle.Get() : nullptr;
        stride = m_selectedInstances ? m_selectedInstances->getLayout()->stride : 0;
        offset = 0;
        deviceContext->IASetVertexBuffers(1, 1, &dxBuf, &stride, &offset);

        dxBuf = m_selectedIBO ? static_cast<DX11GIndexBuffer*>(m_selectedIBO.get())->m_handle.Get() : nullptr;
        deviceContext->IASetIndexBuffer(dxBuf, DXGI_FORMAT_R32_UINT, 0);

        const Layout* vl = m_selectedVBO ? m_selectedVBO->getLayout() : nullptr;
        const Layout* il = m_selectedInstances ? m_selectedInstances->getLayout() : nullptr;
        deviceContext->IASetInputLayout(getLayout(vl, il, m_selectedInstanceStep));
    }

    void DX11GShaderProgram::selectTopology(PrimTopology pt)
    {
        D3D11_PRIMITIVE_TOPOLOGY dx_pt = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
        switch (pt)
        {
        case PrimTopology::Point: dx_pt = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; break;
        case PrimTopology::Line: dx_pt = D3D_PRIMITIVE_TOPOLOGY_LINELIST; break;
        case PrimTopology::Linestrip: dx_pt = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP; break;
        case PrimTopology::Triangle: dx_pt = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
        case PrimTopology::Trianglestrip: dx_pt = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        dx11Device->getDX11DeviceContext()->IASetPrimitiveTopology(dx_pt);
    }

    void DX11GShaderProgram::InputLayoutData::rebuildLayout(ID3D11Device* device, const std::string& shader_code)
    {
        std::vector<D3D11_INPUT_ELEMENT_DESC> descs = {};
        if (vertices)
        {
            for (const auto& f : vertices->fields)
            {
                D3D11_INPUT_ELEMENT_DESC d = {};
                d.SemanticName = f.name.c_str();
                d.SemanticIndex = 0;
                d.Format = ConvertToDX(f);
                d.InputSlot = 0;
                d.AlignedByteOffset = f.offset;
                d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
                d.InstanceDataStepRate = 0;
                descs.push_back(d);
            }
        }
        if (instances)
        {
            for (const auto& f : instances->fields)
            {
                D3D11_INPUT_ELEMENT_DESC d = {};
                d.SemanticName = f.name.c_str();
                d.SemanticIndex = 0;
                d.Format = ConvertToDX(f);
                d.InputSlot = 1;
                d.AlignedByteOffset = f.offset;
                d.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
                d.InstanceDataStepRate = step_rate;
                descs.push_back(d);
            }
        }
        if (descs.size())
        {
            getD3DErr(device->CreateInputLayout(descs.data(), UINT(descs.size()), shader_code.data(), shader_code.size(), &m_dx_layout));
        }
        else
        {
            m_dx_layout = nullptr;
        }
    }  
        
    ID3D11InputLayout* DX11GShaderProgram::getLayout(const Layout* vertices, const Layout* instances, int step_rate)
    {
        for (const auto& l : m_layouts)
        {
            if ((l.vertices == vertices) && (l.instances == instances) && (l.step_rate == step_rate))
            {
                return l.m_dx_layout.Get();
            }
        }

        InputLayoutData new_l;
        new_l.vertices = vertices;
        new_l.instances = instances;
        new_l.step_rate = step_rate;
        
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        new_l.rebuildLayout(dx11Device->getDX11Device(), m_shaderCode[int(ShaderType::Vertex)]);

        m_layouts.push_back(new_l);

        return new_l.m_dx_layout.Get();               
    }

    std::shared_ptr<ShaderProgram::ShaderSlot> DX11GShaderProgram::createNewSlot(SlotKind kind, const std::string& name, const Layout* layout)
    {
        auto newSlot = std::make_shared<DX11GShaderSlot>();
        newSlot->kind = kind;
        newSlot->name = name;
        newSlot->layout = layout;
        return newSlot;
    }

    DX11GUniformBuffer::DX11GUniformBuffer(const GDevicePtr& device) : UniformBuffer(device)
    {

    }

    void DX11GUniformBuffer::setState(const Layout* layout, int elem_count, const void* data)
    {
        UniformBuffer::setState(layout, elem_count, data);

        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = UINT(m_data.size());
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = layout->stride;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        if (data)
        {
            D3D11_SUBRESOURCE_DATA dxData = {};
            dxData.pSysMem = data;
            dxData.SysMemPitch = desc.ByteWidth;
            dxData.SysMemSlicePitch = desc.ByteWidth;
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, &dxData, &m_handle));
        }
        else
        {
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, nullptr, &m_handle));
        }

        m_dirty = false;
    }

    void DX11GUniformBuffer::setSubData(int start_element, int num_elements, const void* data)
    {
        UniformBuffer::setSubData(start_element, num_elements, data);
    }

    void DX11GUniformBuffer::setValue(const char* name, float v, int element_idx)
    {
        UniformBuffer::setValue(name, v, element_idx);
    }
    
    void DX11GUniformBuffer::setValue(const char* name, int i, int element_idx)
    {
        UniformBuffer::setValue(name, i, element_idx);
    }

    void DX11GUniformBuffer::setValue(const char* name, const glm::vec2& v, int element_idx)
    {
        UniformBuffer::setValue(name, v, element_idx);
    }

    void DX11GUniformBuffer::setValue(const char* name, const glm::vec3& v, int element_idx)
    {
        UniformBuffer::setValue(name, v, element_idx);
    }

    void DX11GUniformBuffer::setValue(const char* name, const glm::vec4& v, int element_idx)
    {
        UniformBuffer::setValue(name, v, element_idx);
    }
    
    void DX11GUniformBuffer::setValue(const char* name, const glm::mat4& m, int element_idx)
    {
        UniformBuffer::setValue(name, m, element_idx);
    }

    void DX11GUniformBuffer::validateDynamicData()
    {
        UniformBuffer::validateDynamicData();

        D3D11_MAPPED_SUBRESOURCE map_res = {};

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        getD3DErr(dx11Device->getDX11DeviceContext()->Map(m_handle.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map_res));
        memcpy(map_res.pData, m_data.data(), m_data.size());
        dx11Device->getDX11DeviceContext()->Unmap(m_handle.Get(), 0);
    }

    ComPtr<ID3D11Buffer> DX11GUniformBuffer::getHandle()
    {
        return m_handle;
    }

    DX11GStructuredBuffer::DX11GStructuredBuffer(const GDevicePtr& device) : StructuredBuffer(device)
    {
    
    }

    void DX11GStructuredBuffer::setState(int stride, int vertex_count, bool UAV, bool UAV_with_counter, const void* data)
    {
        m_uav = nullptr;
        m_srv = nullptr;

        m_stride = stride;
        m_vert_count = vertex_count;
        m_UAV_access = UAV;
        m_UAV_with_counter = UAV_with_counter;

        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = glm::max(vertex_count, 1) * m_stride;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        if (UAV)
        {
            desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
        }

        desc.CPUAccessFlags = 0;
        desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        //if (UAV) desc.MiscFlags |= D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
        desc.StructureByteStride = m_stride;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        if (data)
        {
            D3D11_SUBRESOURCE_DATA dxdata = {};
            dxdata.pSysMem = data;
            dxdata.SysMemPitch = desc.ByteWidth;
            dxdata.SysMemSlicePitch = desc.ByteWidth;
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, &dxdata, &m_handle));
        }
        else
        {
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, nullptr, &m_handle));
        }
    }

    void DX11GStructuredBuffer::setSubData(int start_vertex, int num_vertices, const void* data)
    {
        assert(m_handle);
        if (num_vertices <= 0)
        {
            return;
        }

        D3D11_BOX box = {};
        box.left = start_vertex * m_stride;
        box.top = 0;
        box.right = box.left + num_vertices * m_stride;
        box.bottom = 1;
        box.front = 0;
        box.back = 1;
                
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        dx11Device->getDX11DeviceContext()->UpdateSubresource(m_handle.Get(), 0, &box, data, 0, 0);
    }

    ComPtr<ID3D11ShaderResourceView> DX11GStructuredBuffer::getShaderResource()
    {
        if (!m_vert_count)
        {
            return nullptr;
        }

        if (!m_srv)
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
            desc.Format = DXGI_FORMAT_UNKNOWN;
            desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
            desc.Buffer.FirstElement = 0;
            desc.Buffer.NumElements = glm::max(m_vert_count, 1);
            auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
            assert(dx11Device);
            getD3DErr(dx11Device->getDX11Device()->CreateShaderResourceView(m_handle.Get(), &desc, &m_srv));
        }

        return m_srv;
    }

    ComPtr<ID3D11UnorderedAccessView> DX11GStructuredBuffer::getUnorderedAccess()
    {
        assert(m_UAV_access);

        if (!m_uav)
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
            desc.Format = DXGI_FORMAT_UNKNOWN;
            desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
            desc.Buffer.FirstElement = 0;
            desc.Buffer.NumElements = m_vert_count;
            desc.Buffer.Flags = m_UAV_with_counter ? D3D11_BUFFER_UAV_FLAG_COUNTER : 0;
            auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
            assert(dx11Device);
            getD3DErr(dx11Device->getDX11Device()->CreateUnorderedAccessView(m_handle.Get(), &desc, &m_uav));
        }

        return m_uav;
    }

    void DX11GStructuredBuffer::readBack(void* data)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = m_vert_count * m_stride;
        desc.Usage = D3D11_USAGE_STAGING;
        desc.BindFlags = 0;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        desc.StructureByteStride = m_stride;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        ComPtr<ID3D11Buffer> tmp_buf = {};
        getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, nullptr, &tmp_buf));

        dx11Device->getDX11DeviceContext()->CopyResource(tmp_buf.Get(), m_handle.Get());

        D3D11_MAPPED_SUBRESOURCE map = {};
        getD3DErr(dx11Device->getDX11DeviceContext()->Map(tmp_buf.Get(), 0, D3D11_MAP_READ, 0, &map));
        memcpy(data, map.pData, m_vert_count * m_stride);
        dx11Device->getDX11DeviceContext()->Unmap(tmp_buf.Get(), 0);
    }

    DX11GPUTexture2D::DX11GPUTexture2D(const GDevicePtr& device) : GPUTexture2D(device)
    {

    }

    void DX11GPUTexture2D::setState(TextureFmt fmt, int mip_levels)
    {
        m_fmt = fmt;
        m_size = glm::ivec2(0, 0);
        m_slices = 0;
        m_mips_count = mip_levels;
        m_handle = nullptr;
        clearResViews();
    }

    void DX11GPUTexture2D::setState(TextureFmt fmt, glm::ivec2 size, int mip_levels, int slices, const void* data)
    {
        m_fmt = fmt;
        m_size = size;
        m_slices = slices;
        m_mips_count = glm::clamp(mip_levels, 1, calcMipLevelsCount(size.x, size.y));

        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = m_size.x;
        desc.Height = m_size.y;
        desc.MipLevels = m_mips_count;
        desc.ArraySize = m_slices;
        desc.Format = toDXGI_Fmt(m_fmt);
        desc.SampleDesc = { 1, 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = 0;

        if (isShaderRes(m_fmt))
        {
            desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
        }

        if (isRenderTarget(m_fmt))
        {
            desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
        }

        if (isDepthTarget(m_fmt))
        {
            desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
        }

        if (isUAV(m_fmt))
        {
            desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
        }

        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        if ((m_slices % 6 == 0) && isShaderRes(m_fmt))
        {
            desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
        }

        if ((m_mips_count > 0) && isRenderTarget(m_fmt))
        {
            desc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        if (data)
        {
            D3D11_SUBRESOURCE_DATA d3ddata = {};
            d3ddata.pSysMem = data;
            d3ddata.SysMemPitch = getPixelsSize(m_fmt) * m_size.x;
            d3ddata.SysMemSlicePitch = d3ddata.SysMemPitch * m_size.y;
            getD3DErr(dx11Device->getDX11Device()->CreateTexture2D(&desc, &d3ddata, &m_handle));
        }
        else
        {
            getD3DErr(dx11Device->getDX11Device()->CreateTexture2D(&desc, nullptr, &m_handle));
        }

        clearResViews();
    }
    
    void DX11GPUTexture2D::setSubData(const glm::ivec2& offset, const glm::ivec2& size, int slice, int mip, const void* data)
    {
        assert(m_handle);

        UINT res_idx = D3D11CalcSubresource(mip, slice, m_mips_count);

        D3D11_BOX box = {};

        box.left = offset.x;
        box.top = offset.y;
        box.right = offset.x + size.x;
        box.bottom = offset.y + size.y;
        box.front = 0;
        box.back = 1;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        //dx11Device->getDX11DeviceContext()->UpdateSubresource(m_handle.Get(), res_idx, &box, data, getPixelsSize(m_fmt) * size.x, getPixelsSize(m_fmt) * size.x * size.y);
    }

    void DX11GPUTexture2D::generateMips()
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        dx11Device->getDX11DeviceContext()->GenerateMips(getShaderResource(false, false).Get());
    }

    void DX11GPUTexture2D::readBack(void* data, int mip, int array_slice)
    {

    }

    ID3D11ShaderResourceView* DX11GPUTexture2D::_getShaderResView(bool as_array, bool as_cubemap)
    {
        auto srv = getShaderResource(as_array, as_cubemap);
        return srv.Get();
    }

    ComPtr<ID3D11RenderTargetView> DX11GPUTexture2D::buildRenderTarget(int mip, int slice_start, int slice_count) const
    {
        if (!m_handle)
        {
            return nullptr;
        }

        D3D11_RENDER_TARGET_VIEW_DESC desc = {};
        desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
        desc.Format = toDXGI_SRVFmt(m_fmt);
        desc.Texture2DArray.MipSlice = mip;
        desc.Texture2DArray.FirstArraySlice = slice_start;
        desc.Texture2DArray.ArraySize = slice_count;

        ComPtr<ID3D11RenderTargetView> res = {};
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        getD3DErr(dx11Device->getDX11Device()->CreateRenderTargetView(m_handle.Get(), &desc, &res));

        return res;
    }

    ComPtr<ID3D11DepthStencilView> DX11GPUTexture2D::buildDepthStencil(int mip, int slice_start, int slice_count, bool read_only) const
    {
        return ComPtr<ID3D11DepthStencilView>();
    }

    ComPtr<ID3D11ShaderResourceView> DX11GPUTexture2D::getShaderResource(bool as_array, bool as_cubemap)
    {
        as_array = as_array || (m_slices > 1);
        int srv_idx = (as_array ? 1 : 0) | (as_cubemap ? 2 : 0);

        if (!m_srv[srv_idx])
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
            desc.Format = toDXGI_SRVFmt(m_fmt);

            if (as_array)
            {
                if (as_cubemap)
                {
                    desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBEARRAY;
                    desc.TextureCubeArray.MipLevels = m_mips_count;
                    desc.TextureCubeArray.MostDetailedMip = 0;
                    desc.TextureCubeArray.First2DArrayFace = 0;
                    desc.TextureCubeArray.NumCubes = m_slices / 6;
                }
                else
                {
                    desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DARRAY;
                    desc.Texture2DArray.MipLevels = m_mips_count;
                    desc.Texture2DArray.MostDetailedMip = 0;
                    desc.Texture2DArray.ArraySize = m_slices;
                    desc.Texture2DArray.FirstArraySlice = 0;
                }
            }
            else
            {
                if (as_cubemap)
                {
                    desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
                    desc.TextureCube.MipLevels = m_mips_count;
                    desc.TextureCube.MostDetailedMip = 0;
                }
                else
                {
                    desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
                    desc.Texture2D.MipLevels = m_mips_count;
                    desc.Texture2D.MostDetailedMip = 0;
                }
            }
            auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
            assert(dx11Device);
            getD3DErr(dx11Device->getDX11Device()->CreateShaderResourceView(m_handle.Get(), &desc, &m_srv[srv_idx]));
        }

        return m_srv[srv_idx];
    }

    ComPtr<ID3D11UnorderedAccessView> DX11GPUTexture2D::getUnorderedAccess(int mip, int slice_start, int slice_count, bool as_array)
    {
        // Hash key
        glm::ivec3 hk(mip, slice_start, slice_count);

        auto it = m_uav.find(hk);
        if (it == m_uav.end())
        {
            ComPtr<ID3D11UnorderedAccessView> new_view = {};
            D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};

            desc.Format = toDXGI_Fmt(m_fmt);
            bool is_array = (slice_count > 1) || as_array;
            desc.ViewDimension = is_array ? D3D11_UAV_DIMENSION_TEXTURE2DARRAY : D3D11_UAV_DIMENSION_TEXTURE2D;
            if (is_array)
            {
                desc.Texture2DArray.MipSlice = mip;
                desc.Texture2DArray.FirstArraySlice = slice_start;
                desc.Texture2DArray.ArraySize = slice_count;
            }
            else
            {
                desc.Texture2D.MipSlice = mip;
            }

            auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
            assert(dx11Device);
            getD3DErr(dx11Device->getDX11Device()->CreateUnorderedAccessView(m_handle.Get(), &desc, &new_view));

            m_uav.insert({ hk, new_view });

            return new_view;
        }

        return it->second;
    }

    void DX11GPUTexture2D::clearResViews()
    {
        m_uav.clear();
        m_srv[0] = nullptr;
        m_srv[1] = nullptr;
        m_srv[2] = nullptr;
        m_srv[3] = nullptr;
    }

    DX11GVertexBuffer::DX11GVertexBuffer(const GDevicePtr& device) : VertexBuffer(device)
    {

    }

    void DX11GVertexBuffer::setState(const Layout* layout, int vertex_count, const void* data)
    {
        VertexBuffer::setState(layout, vertex_count, data);

        if (!m_vertCount)
        {
            m_handle = nullptr;
            return;
        }

        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = vertex_count * m_layout->stride;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = m_layout->stride;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        if (data)
        {
            D3D11_SUBRESOURCE_DATA dxdata = {};
            dxdata.pSysMem = data;
            dxdata.SysMemPitch = desc.ByteWidth;
            dxdata.SysMemSlicePitch = desc.ByteWidth;
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, &dxdata, &m_handle));
        }
        else
        {
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, nullptr, &m_handle));
        }
    }

    void DX11GVertexBuffer::setSubData(int start_vertex, int num_vertices, const void* data)
    {
        assert(m_handle);
        D3D11_BOX box;
        box.left = start_vertex * m_layout->stride;
        box.top = 0;
        box.right = box.left + num_vertices * m_layout->stride;
        box.bottom = 1;
        box.front = 0;
        box.back = 1;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        dx11Device->getDX11DeviceContext()->UpdateSubresource(m_handle.Get(), 0, &box, data, 0, 0);
    }

    DX11GIndexBuffer::DX11GIndexBuffer(const GDevicePtr& device) : IndexBuffer(device)
    {

    }

    void DX11GIndexBuffer::setState(int ind_count, const void* data)
    {
        IndexBuffer::setState(ind_count, data);

        D3D11_BUFFER_DESC desc;
        desc.ByteWidth = m_indCount * 4;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 4;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);

        if (data)
        {
            D3D11_SUBRESOURCE_DATA dxdata;
            dxdata.pSysMem = data;
            dxdata.SysMemPitch = desc.ByteWidth;
            dxdata.SysMemSlicePitch = desc.ByteWidth;
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, &dxdata, &m_handle));
        }
        else
        {
            getD3DErr(dx11Device->getDX11Device()->CreateBuffer(&desc, nullptr, &m_handle));
        }
    }
    
    void DX11GIndexBuffer::setSubData(int start_idx, int num_indices, const void* data)
    {
        assert(m_handle);
        if (num_indices <= 0) return;
        D3D11_BOX box;
        box.left = start_idx * 4;
        box.top = 0;
        box.right = box.left + num_indices * 4;
        box.bottom = 1;
        box.front = 0;
        box.back = 1;

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        dx11Device->getDX11DeviceContext()->UpdateSubresource(m_handle.Get(), 0, &box, data, 0, 0);
    }

    DX11GFramebuffer::DX11GFramebuffer(const GDevicePtr& device) : Framebuffer(device)
    {

    }

    DX11GFramebuffer::~DX11GFramebuffer()
    {

    }

    void DX11GFramebuffer::clearColorSlot(int slot, const glm::vec4& color)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        dx11Device->getDX11DeviceContext()->ClearRenderTargetView(m_color_views[slot].Get(), (float*)&color);
    }

    void DX11GFramebuffer::clearDS(float depth, bool clear_depth, char stencil, bool clear_stencil)
    {
        if (m_depth_view)
        {
            auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
            assert(dx11Device);
            UINT flags = 0;
            flags |= clear_depth ? D3D11_CLEAR_DEPTH : 0;
            flags |= clear_stencil ? D3D11_CLEAR_STENCIL : 0;
            dx11Device->getDX11DeviceContext()->ClearDepthStencilView(m_depth_view.Get(), flags, depth, stencil);
        }
    }

    void DX11GFramebuffer::setColorSlot(int slot, const GPUTexture2DPtr& tex, int mip, int slice_start, int slice_count)
    {
        if (m_tex[slot] != tex)
        {
            m_tex[slot] = tex;
            m_color_views[slot] = nullptr;
            m_colors_to_bind_dirty = true;
            m_colors_to_bind.clear();
        }

        Tex2DParams new_params(mip, slice_start, slice_count, false, false);

        if (!(m_tex_params[slot] == new_params))
        {
            m_tex_params[slot] = new_params;
            m_color_views[slot] = nullptr;
            m_colors_to_bind_dirty = true;
            m_colors_to_bind.clear();
        }
    }

    void DX11GFramebuffer::setDS(const GPUTexture2DPtr& tex, int mip, int slice_start, int slice_count, bool readonly)
    {
        if (m_depth != tex)
        {
            m_depth = tex;
            m_depth_view = nullptr;
        }

        Tex2DParams new_params(mip, slice_start, slice_count, readonly, false);

        if (!(m_depth_params == new_params))
        {
            m_depth_params = new_params;
            m_depth_view = nullptr;
        }
    }

    void DX11GFramebuffer::clearUAV(int slot, uint32_t v)
    {
        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        UINT clear_value[4] = { v,v,v,v };
        dx11Device->getDX11DeviceContext()->ClearUnorderedAccessViewUint(m_uav_to_bind[slot], clear_value);
    }

    void DX11GFramebuffer::setUAV(int slot, const GPUTexture2DPtr& tex, int mip, int slice_start, int slice_count, bool as_array)
    {
        m_uav_to_bind_count = -1;
        m_uav_to_bind.clear();
        m_uav[slot] = UAVSlot(tex, mip, slice_start, slice_count, as_array);
    }

    void DX11GFramebuffer::setUAV(int slot, const StructuredBufferPtr& buf, int initial_counter)
    {
        m_uav_to_bind_count = -1;
        m_uav_to_bind.clear();
        m_uav[slot] = UAVSlot(buf, initial_counter);
    }

    void DX11GFramebuffer::blitToDefaultFBO(int from_slot)
    {
        if (!m_tex[from_slot])
        {
            return;
        }

        auto gpuTexture = static_cast<DX11GPUTexture2D*>(m_tex[from_slot].get());
        if (!gpuTexture)
        {
            return;
        }

        auto* dx11Device = static_cast<DX11GDevice*>(m_device->getDeviceImpl().get());
        assert(dx11Device);
        const auto& size = m_tex[from_slot]->size();
        const auto& mipsCount = m_tex[from_slot]->mipsCount();

        ID3D11Texture2D* tex = gpuTexture->getHandle().Get();
        D3D11_BOX src_box;
        src_box.left = 0;
        src_box.right = size.x >> m_tex_params[from_slot].mip;
        src_box.top = 0;
        src_box.bottom = size.y >> m_tex_params[from_slot].mip;
        src_box.front = 0;
        src_box.back = 1;
        UINT src_subres = D3D11CalcSubresource(m_tex_params[from_slot].mip, m_tex_params[from_slot].slice_start, mipsCount);
        ComPtr<ID3D11Resource> dest_res;
        //m_device->m_RTView->GetResource(&dest_res);
        dx11Device->getDX11DeviceContext()->CopySubresourceRegion(dest_res.Get(), 0, 0, 0, 0, tex, src_subres, &src_box);
    }

    void DX11GFramebuffer::prepareSlots()
    {
        if (m_colors_to_bind.size() == 0)
        {
            m_rtv_count = 0;
            for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
            {
                if (m_tex[i])
                {
                    m_rtv_count = i + 1;

                    if (!m_color_views[i])
                    {
                        //m_color_views[i] = m_tex[i]->buildRenderTarget(m_tex_params[i].mip, m_tex_params[i].slice_start, m_tex_params[i].slice_count);
                    }

                    m_colors_to_bind.push_back(m_color_views[i].Get());
                }
                else
                {
                    m_colors_to_bind.push_back(nullptr);
                }
            }
        }

        if (m_uav_to_bind_count < 0)
        {
            m_uav_to_bind_count = 0;
            for (int i = m_rtv_count; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT + D3D11_PS_CS_UAV_REGISTER_COUNT; i++)
            {
                if (m_uav[i].kind != UAV_slot_kind::empty)
                {
                    m_uav_to_bind_count++;
                }
            }
        }

        m_uav_to_bind.clear();
        m_uav_initial_counts.clear();

        if (m_uav_to_bind_count > 0)
        {
            for (int i = m_rtv_count; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT + D3D11_PS_CS_UAV_REGISTER_COUNT; i++)
            {
                switch (m_uav[i].kind)
                {
                    case (UAV_slot_kind::tex):
                    {
                        auto texture = static_cast<DX11GPUTexture2D*>(m_uav[i].tex.get());
                        m_uav_to_bind.push_back(texture->getUnorderedAccess(m_uav[i].tex_params.mip, m_uav[i].tex_params.slice_start, m_uav[i].tex_params.slice_count, m_uav[i].tex_params.as_array).Get());
                        m_uav_initial_counts.push_back(m_uav[i].initial_counter);
                        break;
                    }                    
                    case (UAV_slot_kind::buf):
                    {
                        auto buffer = static_cast<DX11GStructuredBuffer*>(m_uav[i].buf.get());
                        m_uav_to_bind.push_back(buffer->getUnorderedAccess().Get());
                        m_uav_initial_counts.push_back(m_uav[i].initial_counter);
                        break;
                    }                    
                    case (UAV_slot_kind::empty):
                    {
                        m_uav_to_bind.push_back(nullptr);
                        m_uav_initial_counts.push_back(-1);
                        break;
                    }                    
                }
            }
        }

        if (m_depth && (!m_depth_view))
        {
            auto depthTexture = static_cast<DX11GPUTexture2D*>(m_depth.get());
            m_depth_view = depthTexture->buildDepthStencil(m_depth_params.mip, m_depth_params.slice_start, m_depth_params.slice_count, m_depth_params.read_only);
        }
    }

    void DX11GFramebuffer::setSize(const glm::ivec2& xy)
    {
        if (m_size != xy)
        {
            for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
                m_color_views[i] = nullptr;
            m_depth_view = nullptr;
            m_colors_to_bind.clear();
        }

        m_size = xy;

        for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
        {
            if (!m_tex[i]) continue;
            if (m_tex[i]->size() != xy)
            {
                m_tex[i]->setState(m_tex[i]->format(), xy, m_tex[i]->mipsCount(), 1);
                m_color_views[i] = nullptr;
                m_colors_to_bind.clear();
            }
        }

        if (m_depth)
        {
            if (m_depth->size() != xy)
            {
                m_depth->setState(m_depth->format(), xy, m_depth->mipsCount(), 1);
                m_depth_view = nullptr;
            }
        }
    }

}