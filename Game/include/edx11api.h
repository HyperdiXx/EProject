#pragma once

#include <egapi.h>

#include <glmh.h>

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3d11shader.h>
#include <d3dcompiler.h>

#include <stdexcept>
#include <memory>
#include <wrl.h>

namespace EProject
{
    using namespace Microsoft::WRL;
    
    class DX11GFramebuffer;
    class DX11GPUTexture2D;
    class DX11GShaderProgram;
    class DX11GStates;
    class DX11GVertexBuffer;
    class DX11GIndexBuffer;
    class DX11GUniformBuffer;
    class DX11GStructuredBuffer;

    using DX11GFrameBufferPtr = std::shared_ptr<DX11GFramebuffer>;
    using DX11GPUTexture2DPtr = std::shared_ptr<DX11GPUTexture2D>;
    using DX11GShaderProgramPtr = std::shared_ptr<DX11GShaderProgram>;
    using DX11GVertexBufferPtr = std::shared_ptr<DX11GVertexBuffer>;
    using DX11GIndexBufferPtr = std::shared_ptr<DX11GIndexBuffer>;
    using DX11GUniformBufferPtr = std::shared_ptr<DX11GUniformBuffer>;
    using DX11GStructuredBufferPtr = std::shared_ptr<DX11GStructuredBuffer>;
   
    class DX11GDevice : public GDeviceAPI
    {
    public:
        DX11GDevice(const GDevicePtr& device);

        void init(const WindowParameters& params) override;
        void shutdown() override;

        FrameBufferPtr createFramebuffer() override;
        GPUTexture2DPtr createTexture2D() override;
        IndexBufferPtr createIndexBuffer() override;
        VertexBufferPtr createVertexBuffer() override;
        ShaderProgramPtr createShaderProgram() override;
        UniformBufferPtr createUniformBuffer() override;
        StructuredBufferPtr createStructuredBuffer() override;

        void endFrame() override;

        void draw(int vert_start, int vert_count, int instance_count, int base_instance) override;
        void drawIndexed(int index_start, int index_count, int instance_count, int base_vertex, int base_instance) override;

        GDeviceAPI* getDevicePtrRaw() override;
        GSamplerState* obtainSamplerState(const Sampler& s) override;
        GStates* getStates() override;

        bool createDefaultRTV(const WindowParameters& params) override;
        void setDefaultFramebuffer() override;
        void setViewport(const glm::vec2& size) override;
        void clearRenderTarget(const float* color = {}, bool clearDepth = true) override;
    
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
    
        GDevicePtr m_devicePtr;
    };

    class DX11GSamplerState : public GSamplerState
    {
    public:
        DX11GSamplerState() = default;
        DX11GSamplerState(ComPtr<ID3D11SamplerState> ptr);

        ComPtr<ID3D11SamplerState>& getStatePtr() { return m_state; };
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
        struct DX11GShaderSlot : public ShaderProgram::ShaderSlot
        {
            ComPtr<ID3D11ShaderResourceView> view;
            ComPtr<ID3D11Buffer> buffer;
            ID3D11SamplerState* sampler = nullptr;

            void select(ID3D11DeviceContext* dev) const;            
        };

        struct InputLayoutData
        {
            const Layout* vertices = nullptr;
            const Layout* instances = nullptr;
            int step_rate = 0;
            ComPtr<ID3D11InputLayout> m_dx_layout = 0;
            InputLayoutData() = default;
            void rebuildLayout(ID3D11Device* device, const std::string& shader_code);
        };

    public:
        DX11GShaderProgram(const GDevicePtr& device);
        ~DX11GShaderProgram();

        bool compileFromFile(const ShaderInput& input) override;
        bool create() override;

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

        void selectShaderSlots() override;
        void selectInputBuffers() override;
        void selectShaderPrograms() override;
        void selectTopology(PrimTopology pt);

        ID3D11InputLayout* getLayout(const Layout* vertices, const Layout* instances, int step_rate);
        std::shared_ptr<ShaderProgram::ShaderSlot> createNewSlot(SlotKind kind, const std::string& name, const Layout* layout) override;
    private:
        ID3D10Blob* m_shaderData[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
        ComPtr<ID3D11DeviceChild> m_shaders[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

        std::vector<InputLayoutData> m_layouts;
    };

    class DX11GVertexBuffer : public VertexBuffer
    {
        friend class DX11GShaderProgram;
    public:
        DX11GVertexBuffer(const GDevicePtr& device);

        void setState(const Layout* layout, int vertex_count, const void* data = nullptr) override;
        void setSubData(int start_vertex, int num_vertices, const void* data) override;
    private:
        ComPtr<ID3D11Buffer> m_handle;
    };

    class DX11GIndexBuffer : public IndexBuffer
    {
        friend class DX11GShaderProgram;
    public:
        DX11GIndexBuffer(const GDevicePtr& device);

        void setState(int ind_count, const void* data = nullptr) override;
        void setSubData(int start_idx, int num_indices, const void* data) override;
    private:
        ComPtr<ID3D11Buffer> m_handle;
    };

    class DX11GStructuredBuffer : public StructuredBuffer
    {
        friend class DX11GShaderProgram;
        friend class DX11GFramebuffer;
    public:
        DX11GStructuredBuffer(const GDevicePtr& device);

        void setState(int stride, int vertex_count, bool UAV = false, bool UAV_with_counter = false, const void* data = nullptr) override;
        void setSubData(int start_vertex, int num_vertices, const void* data) override;

        void readBack(void* data) override;

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

    class DX11GPUTexture2D : public GPUTexture2D
    {
        friend class DX11GFramebuffer;
        friend class DX11GShaderProgram;
    public:
        DX11GPUTexture2D(const GDevicePtr& device);

        void setState(TextureFmt fmt, int mip_levels = 0) override;
        void setState(TextureFmt fmt, glm::ivec2 size, int mip_levels = 0, int slices = 1, const void* data = nullptr) override;
        void setSubData(const glm::ivec2& offset, const glm::ivec2& size, int slice, int mip, const void* data) override;
        void generateMips() override;

        void readBack(void* data, int mip, int array_slice) override;

        ID3D11ShaderResourceView* _getShaderResView(bool as_array, bool as_cubemap);
        ComPtr<ID3D11Texture2D> getHandle() { return m_handle; };
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
    };

    class DX11GFramebuffer : public Framebuffer
    {
        friend class GDevice;
    private:
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
        DX11GFramebuffer(const GDevicePtr& device);
        ~DX11GFramebuffer();

        void clearColorSlot(int slot, const glm::vec4& color) override;
        void clearDS(float depth, bool clear_depth = true, char stencil = 0, bool clear_stencil = false) override;

        void setColorSlot(int slot, const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1) override;
        void setDS(const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1, bool readonly = false) override;

        void clearUAV(int slot, uint32_t v) override;
        void setUAV(int slot, const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1, bool as_array = false) override;
        void setUAV(int slot, const StructuredBufferPtr& buf, int initial_counter = -1) override;

        void blitToDefaultFBO(int from_slot) override;
        void setSize(const glm::ivec2& xy) override;
        void prepareSlots() override;
    private:
        UAVSlot m_uav[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT + G_D3D11_PS_CS_UAV_REGISTER_COUNT];

        ComPtr<ID3D11RenderTargetView> m_color_views[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        ComPtr<ID3D11DepthStencilView> m_depth_view;

        std::vector<ID3D11RenderTargetView*> m_colors_to_bind;
        std::vector<ID3D11UnorderedAccessView*> m_uav_to_bind;
    };
}
