#pragma once

#include <egapi.h>

#include <stdexcept>
#include <memory>
#include <wrl.h>

#include <glmh.h>

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3d11shader.h>
#include <d3dcompiler.h>

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

    using namespace Microsoft::WRL;
    
    class DX11GStates;

    class DX11GDevice : public GDeviceAPI
    {
    public:
        DX11GDevice() = default;

        void init(const WindowParameters& params) override;
        void shutdown() override;

        FrameBufferPtr createFramebuffer() override;
        GPUTexture2DPtr createTexture2D() override;
        IndexBufferPtr createIndexBuffer() override;
        VertexBufferPtr createVertexBuffer() override;
        ShaderProgramPtr createShaderProgram() override;
        UniformBufferPtr createUniformBuffer() override;
        StructuredBufferPtr createStructuredBuffer() override;

        GDeviceAPI* getDevicePtr() override;
        GSamplerState* obtainSamplerState(const Sampler& s) override;
        GStates* getStates() override;

        ID3D11Device* getDX11Device() const;
        ID3D11DeviceContext* getDX11DeviceContext() const;
    private:
        ComPtr<ID3D11Device> m_dev;
        ComPtr<ID3D11DeviceContext> m_context;
        ComPtr<IDXGISwapChain> m_swapChain;

        ComPtr<ID3D11Texture2D> m_backBuffer;
        ComPtr<ID3D11Texture2D> m_depthStencil;

        ComPtr<ID3D11RenderTargetView> m_RTView;
        ComPtr<ID3D11DepthStencilView> m_depthStencilView;

        std::unique_ptr<DX11GStates> m_states;

        std::unordered_map<Sampler, ComPtr<ID3D11SamplerState>, Sampler> m_samplers;
    };

    class DX11GSamplerState : public GSamplerState
    {
    public:
        DX11GSamplerState() = default;
        DX11GSamplerState(ComPtr<ID3D11SamplerState> ptr);
    private:
        ComPtr<ID3D11SamplerState> m_state;
    };

    class DX11GStates : public GStates
    {
    private:
        struct StateData
        {
            D3D11_RASTERIZER_DESC m_r_desc;
            ComPtr<ID3D11RasterizerState> m_r_state;
            UINT m_stencil_ref;
            D3D11_DEPTH_STENCIL_DESC m_d_desc;
            ComPtr<ID3D11DepthStencilState> m_d_state;
            D3D11_BLEND_DESC m_b_desc;
            ComPtr<ID3D11BlendState> m_b_state;

            inline StateData(DX11GStates* st)
            {
                m_r_desc = st->m_r_desc;
                m_d_desc = st->m_d_desc;
                m_b_desc = st->m_b_desc;
                m_r_state = st->m_r_state;
                m_d_state = st->m_d_state;
                m_b_state = st->m_b_state;
                m_stencil_ref = st->m_stencil_ref;
            }
        };
    private:
        ID3D11Device* m_device;
        ID3D11DeviceContext* m_deviceContext;

        D3D11_RASTERIZER_DESC m_r_desc;
        ComPtr<ID3D11RasterizerState> m_r_state;

        UINT m_stencil_ref;
        D3D11_DEPTH_STENCIL_DESC m_d_desc;
        ComPtr<ID3D11DepthStencilState> m_d_state;

        D3D11_BLEND_DESC m_b_desc;
        ComPtr<ID3D11BlendState> m_b_state;

        std::vector<StateData> m_states;
    private:
        void setDefaultStates();
    public:
        void validateStates() override;
        void push() override;
        void pop() override;

        void setWireframe(bool wire) override;
        void setCull(CullMode cm) override;

        void setDepthEnable(bool enable) override;
        void setDepthWrite(bool enable) override;
        void setDepthFunc(Compare cmp) override;

        void setBlend(bool enable, Blend src = Blend::One, Blend dst = Blend::One, int rt_index = -1, BlendFunc bf = BlendFunc::Add) override;
        void setBlendSeparateAlpha(bool enable, Blend src_color = Blend::One, Blend dst_color = Blend::One, BlendFunc bf_color = BlendFunc::Add,
            Blend src_alpha = Blend::One, Blend dst_alpha = Blend::One, BlendFunc bf_alpha = BlendFunc::Add,
            int rt_index = -1) override;

        void setColorWrite(bool enable, int rt_index = -1) override;

        DX11GStates(ID3D11Device* device, ID3D11DeviceContext* device_context);
    };

    class DX11GShaderProgram : public ShaderProgram
    {
    private:

        const ShaderType cShaders[6] = { ShaderType::Vertex, ShaderType::Hull, ShaderType::Domain, ShaderType::Geometry, ShaderType::Pixel, ShaderType::Compute };

        enum class SlotKind { Uniform, Texture, Buffer, Sampler };

        struct ShaderSlot
        {
            SlotKind kind;
            std::string name;
            const Layout* layout;
            int bindPoints[6] = { -1,-1,-1,-1,-1,-1 };

            ComPtr<ID3D11ShaderResourceView> view;
            ComPtr<ID3D11Buffer> buffer;
            ID3D11SamplerState* sampler;

            void select(ID3D11DeviceContext* dev) const;
            ShaderSlot() : kind(SlotKind::Uniform), layout(nullptr), sampler(nullptr) {}
        };

        struct InputLayoutData
        {
            const Layout* vertices;
            const Layout* instances;
            int step_rate;
            ComPtr<ID3D11InputLayout> m_dx_layout;
            InputLayoutData();
            void rebuildLayout(ID3D11Device* device, const std::string& shader_code);
        };

    public:

        DX11GShaderProgram(const GDevicePtr& device);
        ~DX11GShaderProgram();

        bool compileFromFile(const ShaderInput& input);
        bool create();

        void activateProgram();
        void setInputBuffers(const VertexBufferPtr& vbo, const IndexBufferPtr& ibo, const VertexBufferPtr& instances, int instanceStepRate);

        void drawIndexed(PrimTopology pt, const DrawIndexedCmd& cmd);
        void drawIndexed(PrimTopology pt, const std::vector<DrawIndexedCmd>& cmd_buf);
        void drawIndexed(PrimTopology pt, int index_start = 0, int index_count = -1, int instance_count = -1, int base_vertex = 0, int base_instance = 0);
        void draw(PrimTopology pt, int vert_start = 0, int vert_count = -1, int instance_count = -1, int base_instance = 0);

        void setValue(const char* name, float v);
        void setValue(const char* name, int i);
        void setValue(const char* name, const glm::vec2& v);
        void setValue(const char* name, const glm::vec3& v);
        void setValue(const char* name, const glm::vec4& v);
        void setValue(const char* name, const glm::mat4& m);

        void setResource(const char* name, const UniformBufferPtr& ubo);
        void setResource(const char* name, const StructuredBufferPtr& sbo);
        void setResource(const char* name, const GPUTexture2DPtr& tex, bool as_array = false, bool as_cubemap = false);
        //void setResource(const char* name, const Texture3DPtr& tex);
        void setResource(const char* name, const Sampler& s);


    private:
        const Layout* autoReflectCB(ID3D11ShaderReflectionConstantBuffer* cb_ref);
        void autoReflect(const void* data, int data_size, ShaderType st);

        void selectInputBuffers();
        void selectTopology(PrimTopology pt);

        bool isProgramActive() const;

        ID3D11InputLayout* getLayout(const Layout* vertices, const Layout* instances, int step_rate);

        int obtainSlotIdx(SlotKind kind, const std::string& name, const Layout* layout);
        int findSlot(const char* name);

    private:

        UniformBufferPtr m_ub[6];
        bool m_globals_dirty;

        ID3D10Blob* m_shaderData[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
        std::array<std::string, 6> m_shaderCode = { std::string(), std::string(), std::string(), std::string(), std::string(), std::string() };
        ComPtr<ID3D11DeviceChild> m_shaders[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

        std::vector<ShaderSlot> m_slots;

        VertexBufferPtr m_selectedVBO;
        IndexBufferPtr m_selectedIBO;
        VertexBufferPtr m_selectedInstances;
        int m_selectedInstanceStep;

        std::vector<InputLayoutData> m_layouts;

    };

    class VertexBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
    public:
        VertexBuffer(const GDevicePtr& device);

        void setState(const Layout* layout, int vertex_count, const void* data = nullptr);
        void setSubData(int start_vertex, int num_vertices, const void* data);

        int getVertexCount() const;
        const Layout* getLayout() const;
    private:
        const Layout* m_layout = nullptr;
        ComPtr<ID3D11Buffer> m_handle;
        int m_vertCount = 0;
    };

    class IndexBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
    public:
        IndexBuffer(const GDevicePtr& device);

        void setState(int ind_count, const void* data = nullptr);
        void setSubData(int start_idx, int num_indices, const void* data);

        int getIndexCount() const;

    private:
        ComPtr<ID3D11Buffer> m_handle;
        int m_indCount = 0;
    };

    class StructuredBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
        friend class Framebuffer;
    public:
        StructuredBuffer(const GDevicePtr& device);

        void setState(int stride, int vertex_count, bool UAV = false, bool UAV_with_counter = false, const void* data = nullptr);
        void setSubData(int start_vertex, int num_vertices, const void* data);

        void readBack(void* data);

        int getStride() const;
        int getVertexCount() const;

    private:
        ComPtr<ID3D11ShaderResourceView> getShaderResource();
        ComPtr<ID3D11UnorderedAccessView> getUnorderedAccess();

    private:
        ComPtr<ID3D11Buffer> m_handle;
        ComPtr<ID3D11ShaderResourceView> m_srv;
        ComPtr<ID3D11UnorderedAccessView> m_uav;
        int m_stride = 0;
        int m_vert_count = 0;
        bool m_UAV_access = false;
        bool m_UAV_with_counter = false;
    };

    class DX11GUniformBuffer : public UniformBuffer
    {
    public:
        DX11GUniformBuffer(const GDevicePtr& device);

        void setState(const Layout* layout, int elemets_count, const void* data = nullptr);
        void setSubData(int start_element, int num_elements, const void* data);
        void setValue(const char* name, float v, int element_idx = 0);
        void setValue(const char* name, int i, int element_idx = 0);
        void setValue(const char* name, const glm::vec2& v, int element_idx = 0);
        void setValue(const char* name, const glm::vec3& v, int element_idx = 0);
        void setValue(const char* name, const glm::vec4& v, int element_idx = 0);
        void setValue(const char* name, const glm::mat4& m, int element_idx = 0);
        void validateDynamicData();

        ComPtr<ID3D11Buffer> getHandle();
    private:
        ComPtr<ID3D11Buffer> m_handle;
    };

    class GPUTexture2D : public DeviceHolder
    {
        friend class Framebuffer;
        friend class ShaderProgram;
    public:
        GPUTexture2D(const GDevicePtr& device);

        TextureFmt format() const;
        glm::ivec2 size() const;
        int slicesCount() const;
        int mipsCount() const;
        void setState(TextureFmt fmt, int mip_levels = 0);
        void setState(TextureFmt fmt, glm::ivec2 size, int mip_levels = 0, int slices = 1, const void* data = nullptr);
        void setSubData(const glm::ivec2& offset, const glm::ivec2& size, int slice, int mip, const void* data);
        void generateMips();

        void readBack(void* data, int mip, int array_slice);

        ID3D11ShaderResourceView* _getShaderResView(bool as_array, bool as_cubemap);
    private:
        struct ivec3_hasher
        {
            std::size_t operator() (const glm::ivec3& v) const
            {
                return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
            }
        };

        struct ivec2_hasher
        {
            std::size_t operator() (const glm::ivec2& v) const
            {
                return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
            }
        };

    private:
        ComPtr<ID3D11RenderTargetView> buildRenderTarget(int mip, int slice_start, int slice_count) const;
        ComPtr<ID3D11DepthStencilView> buildDepthStencil(int mip, int slice_start, int slice_count, bool read_only) const;
        ComPtr<ID3D11ShaderResourceView> getShaderResource(bool as_array, bool as_cubemap);
        ComPtr<ID3D11UnorderedAccessView> getUnorderedAccess(int mip, int slice_start, int slice_count, bool as_array);

        void clearResViews();

    private:
        ComPtr<ID3D11Texture2D> m_handle;
        ComPtr<ID3D11ShaderResourceView> m_srv[4];

        std::unordered_map<glm::ivec3, ComPtr<ID3D11UnorderedAccessView>, ivec3_hasher> m_uav;

        TextureFmt m_fmt;
        glm::ivec2 m_size;
        int m_slices;
        int m_mips_count;
    };

    static int getPixelsSize(TextureFmt fmt);

    class Framebuffer : public DeviceHolder
    {
        friend class GDevice;
    private:
        struct Tex2DParams
        {
            int mip;
            int slice_start;
            int slice_count;
            bool read_only;
            bool as_array;
            Tex2DParams();
            Tex2DParams(int mip, int slice_start, int slice_count, bool ronly, bool as_array);
            bool operator == (const Tex2DParams& b);
        };

        enum class UAV_slot_kind { empty, tex, buf };
        struct UAVSlot
        {
            UAV_slot_kind kind;
            GPUTexture2DPtr tex;
            Tex2DParams tex_params;
            StructuredBufferPtr buf;
            ComPtr<ID3D11UnorderedAccessView> view;
            int initial_counter;

            UAVSlot()
            {
                kind = UAV_slot_kind::empty;
                this->tex = nullptr;
                this->buf = nullptr;
            }

            UAVSlot(const GPUTexture2DPtr& tex, int mip, int slice_start, int slice_count, bool as_array)
            {
                kind = UAV_slot_kind::tex;
                buf = nullptr;
                this->tex = tex;
                tex_params.mip = mip;
                tex_params.read_only = false;
                tex_params.slice_count = slice_count;
                tex_params.slice_start = slice_start;
                tex_params.as_array = as_array;
                this->initial_counter = -1;
            }

            UAVSlot(const StructuredBufferPtr& buf, int initial_counter)
            {
                kind = UAV_slot_kind::buf;
                this->buf = buf;
                this->tex = nullptr;
                this->initial_counter = initial_counter;
            }
        };

    public:

        Framebuffer(const GDevicePtr& device);
        ~Framebuffer();

        void clearColorSlot(int slot, const glm::vec4& color);
        void clearDS(float depth, bool clear_depth = true, char stencil = 0, bool clear_stencil = false);

        void setColorSlot(int slot, const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1);
        void setDS(const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1, bool readonly = false);
        GPUTexture2DPtr getColorSlot(int slot) const;
        GPUTexture2DPtr getDS() const;

        void clearUAV(int slot, uint32_t v);
        void setUAV(int slot, const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1, bool as_array = false);
        void setUAV(int slot, const StructuredBufferPtr& buf, int initial_counter = -1);

        void blitToDefaultFBO(int from_slot);

        void setSizeFromWindow();
        void setSize(const glm::ivec2& xy);
        glm::ivec2 getSize() const;
    private:
        void prepareSlots();
    private:

        GPUTexture2DPtr m_tex[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        GPUTexture2DPtr m_depth;

        Tex2DParams m_tex_params[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        Tex2DParams m_depth_params;

        UAVSlot m_uav[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT + G_D3D11_PS_CS_UAV_REGISTER_COUNT];

        ComPtr<ID3D11RenderTargetView> m_color_views[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        ComPtr<ID3D11DepthStencilView> m_depth_view;

        std::vector<ID3D11RenderTargetView*> m_colors_to_bind;
        std::vector<ID3D11UnorderedAccessView*> m_uav_to_bind;
        std::vector<UINT> m_uav_initial_counts;

        glm::ivec2 m_size;
        int m_rtv_count = 0;
        int m_uav_to_bind_count = 0;

        bool m_colors_to_bind_dirty = false;
    };
}
