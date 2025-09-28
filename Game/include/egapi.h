#pragma once

#include <wrl.h>
#include <glmh.h>
#include <array>

namespace EProject
{
    using namespace Microsoft::WRL;

    const uint32_t G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT = 8;
    const uint32_t G_D3D11_PS_CS_UAV_REGISTER_COUNT = 8;

    enum class TextureFmt
    {
        None,
        R8, RG8, RGBA8, RGBA8_SRGB,
        R16, RG16, RGBA16,
        R16f, RG16f, RGBA16f,
        R32, RG32, RGB32, RGBA32,
        R32f, RG32f, RGB32f, RGBA32f,
        D16, D24_S8, D32f, D32f_S8,
    };

    enum class PrimTopology
    {
        Point,
        Line,
        Linestrip,
        Triangle,
        Trianglestrip,
    };

    enum class TexFilter { None, Point, Linear };
    enum class TexWrap { Repeat, Mirror, Clamp, ClampBorder };

    enum class CullMode { None, Back, Front };
    enum class Compare { Never, Less, Equal, Less_Equal, Greater, Not_Equal, Greater_Equal, Always };
    enum class StencilOp { Keep, Zero, Replace, Inc_Clamp, Dec_Clamp, Ind, Dec };
    enum class BlendFunc { Add, Sub, Rev_Sub, Min, Max };
    enum class Blend { Zero, One, Src_Alpha, Inv_Src_Alpha, Dst_Alpha, Inv_Dst_Alpha, Src_Color, Inv_Src_Color, Dst_Color, Inv_Dst_Color };

    struct Sampler
    {
        TexFilter filter;
        TexFilter mipfilter;
        int anisotropy;
        TexWrap wrap_x;
        TexWrap wrap_y;
        TexWrap wrap_z;
        glm::vec4 border;
        Compare comparison;

        bool operator==(const Sampler& p) const
        {
            return memcmp(this, &p, sizeof(Sampler)) == 0;
        }

        std::size_t operator() (const Sampler& s) const
        {
            return std::hash<TexFilter>()(filter) ^ std::hash<TexFilter>()(mipfilter) ^ std::hash<int>()(anisotropy) ^
                   std::hash<TexWrap>()(wrap_x) ^ std::hash<TexWrap>()(wrap_y) ^ std::hash<TexWrap>()(wrap_z) ^ 
                   std::hash<glm::vec4>()(border) ^ std::hash<Compare>()(comparison);
        }
    };

    constexpr static Sampler cSampler_Linear
    {
        TexFilter::Linear, TexFilter::Linear, 16,
        TexWrap::Repeat, TexWrap::Repeat, TexWrap::Repeat, {0,0,0,0},
        Compare::Never
    };

    constexpr static Sampler cSampler_LinearClamped
    {
        TexFilter::Linear, TexFilter::Linear, 16,
        TexWrap::Clamp, TexWrap::Clamp, TexWrap::Clamp, {0,0,0,0},
        Compare::Never
    };

    constexpr static Sampler cSampler_NoFilter
    {
        TexFilter::Point, TexFilter::None, 0,
        TexWrap::Repeat, TexWrap::Repeat, TexWrap::Repeat, {0,0,0,0},
        Compare::Never
    };

    struct DrawIndexedCmd
    {
        UINT indexCount;
        UINT instanceCount;
        UINT startIndex;
        INT  baseVertex;
        UINT baseInstance;
    };

    static bool isShaderRes(TextureFmt fmt)
    {
        return fmt != TextureFmt::D24_S8;
    }

    static bool isRenderTarget(TextureFmt fmt)
    {
        return
            (fmt == TextureFmt::R8) ||
            (fmt == TextureFmt::RG8) ||
            (fmt == TextureFmt::RGBA8) ||
            (fmt == TextureFmt::RGBA8_SRGB) ||
            (fmt == TextureFmt::R16f) ||
            (fmt == TextureFmt::RG16f) ||
            (fmt == TextureFmt::RGBA16f) ||
            (fmt == TextureFmt::R32f) ||
            (fmt == TextureFmt::RG32f) ||
            (fmt == TextureFmt::RGB32f) ||
            (fmt == TextureFmt::RGBA32f);
    }

    static bool isDepthTarget(TextureFmt fmt)
    {
        return
            (fmt == TextureFmt::D16) ||
            (fmt == TextureFmt::D24_S8) ||
            (fmt == TextureFmt::D32f) ||
            (fmt == TextureFmt::D32f_S8);
    }

    static bool isUAV(TextureFmt fmt)
    {
        return
            (fmt == TextureFmt::R32) ||
            (fmt == TextureFmt::RG32) ||
            (fmt == TextureFmt::RGB32) ||
            (fmt == TextureFmt::RGBA32) ||
            (fmt == TextureFmt::R32f) ||
            (fmt == TextureFmt::RG32f) ||
            (fmt == TextureFmt::RGB32f) ||
            (fmt == TextureFmt::RGBA32f);
    }

    static int calcMipLevelsCount(int w, int h)
    {
        assert(w >= 0);
        assert(h >= 0);

        int min_size = glm::min(w, h);
        int max_mip = 0;
        while (min_size > 0) {
            min_size >>= 1;
            max_mip++;
        }
        return max_mip;
    }

    static int calcMipLevelsCount(int w, int h, int z)
    {
        assert(w >= 0);
        assert(h >= 0);

        int min_size = glm::min(glm::min(w, h), z);
        int max_mip = 0;
        while (min_size > 0) {
            min_size >>= 1;
            max_mip++;
        }
        return max_mip;
    }

    static int getPixelsSize(TextureFmt fmt)
    {
        switch (fmt) {
        case TextureFmt::R8: return 1;
        case TextureFmt::RG8: return 2;
        case TextureFmt::RGBA8: return 4;
        case TextureFmt::RGBA8_SRGB: return 4;
        case TextureFmt::R16: return 2;
        case TextureFmt::RG16: return 4;
        case TextureFmt::RGBA16: return 8;
        case TextureFmt::R16f: return 2;
        case TextureFmt::RG16f: return 4;
        case TextureFmt::RGBA16f: return 8;
        case TextureFmt::R32: return 4;
        case TextureFmt::RG32: return 8;
        case TextureFmt::RGB32: return 12;
        case TextureFmt::RGBA32: return 16;
        case TextureFmt::R32f: return 4;
        case TextureFmt::RG32f: return 8;
        case TextureFmt::RGB32f: return 12;
        case TextureFmt::RGBA32f: return 16;
        case TextureFmt::D16: return 2;
        case TextureFmt::D24_S8: return 4;
        case TextureFmt::D32f: return 4;
        case TextureFmt::D32f_S8: return 8;
        default:
            return 0;
        }
    }

    class ShaderProgram;
    class VertexBuffer;
    class IndexBuffer;
    class UniformBuffer;
    class StructuredBuffer;
    class GPUTexture2D;
    class Framebuffer;
    class GStates;

    using FrameBufferPtr = std::shared_ptr<Framebuffer>;
    using GPUTexture2DPtr = std::shared_ptr<GPUTexture2D>;
    using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;
    using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
    using IndexBufferPtr = std::shared_ptr<IndexBuffer>;
    using UniformBufferPtr = std::shared_ptr<UniformBuffer>;
    using StructuredBufferPtr = std::shared_ptr<StructuredBuffer>;
    using GStatesPtr = std::shared_ptr<GStates>;

    struct WindowParameters
    {
        HWND hwnd;
        std::string name;
        glm::ivec2 size;
        bool isSrgb;
    };

    class GSamplerState
    {
    public:
        GSamplerState() = default;
    private:
    };

    class GDeviceAPI
    {
    public:
        virtual void init(const WindowParameters& params) = 0;
        virtual void shutdown() = 0;

        virtual FrameBufferPtr createFramebuffer() = 0;
        virtual GPUTexture2DPtr createTexture2D() = 0;
        virtual IndexBufferPtr createIndexBuffer() = 0;
        virtual VertexBufferPtr createVertexBuffer() = 0;
        virtual ShaderProgramPtr createShaderProgram() = 0;
        virtual UniformBufferPtr createUniformBuffer() = 0;
        virtual StructuredBufferPtr createStructuredBuffer() = 0;

        virtual void endFrame() = 0;

        virtual GDeviceAPI* getDevicePtrRaw() = 0;
        virtual GSamplerState* obtainSamplerState(const Sampler& s) = 0;
        virtual GStates* getStates() = 0;
        virtual bool createDefaultRTV(const WindowParameters& params) = 0;
        virtual void setDefaultFramebuffer() = 0;
        virtual void setViewport(const glm::vec2& size) = 0;
        virtual void clearRenderTarget(const float* color = {}, bool clearDepth = true) = 0;
    private:
    };

    class GStates
    {
    public:        
        virtual void validateStates() = 0;
        virtual void push() = 0;
        virtual void pop() = 0;

        virtual void setWireframe(bool wire) = 0;
        virtual void setCull(CullMode cm) = 0;

        virtual void setDepthEnable(bool enable) = 0;
        virtual void setDepthWrite(bool enable) = 0;
        virtual void setDepthFunc(Compare cmp) = 0;

        virtual void setBlend(bool enable, Blend src = Blend::One, Blend dst = Blend::One, int rt_index = -1, BlendFunc bf = BlendFunc::Add) = 0;
        virtual void setBlendSeparateAlpha(bool enable, Blend src_color = Blend::One, Blend dst_color = Blend::One, BlendFunc bf_color = BlendFunc::Add,
            Blend src_alpha = Blend::One, Blend dst_alpha = Blend::One, BlendFunc bf_alpha = BlendFunc::Add,
            int rt_index = -1) = 0;

        virtual void setColorWrite(bool enable, int rt_index = -1) = 0;
    };

    class GDevice : public std::enable_shared_from_this<GDevice>
    {
        friend class ShaderProgram;
        friend class VertexBuffer;
        friend class IndexBuffer;
        friend class UniformBuffer;
        friend class StructuredBuffer;
        friend class GPUTexture2D;
        friend class Framebuffer;
    public:
        GDevice(HWND wnd, bool sRGB);
        ~GDevice();

        FrameBufferPtr setFrameBuffer(const FrameBufferPtr& fbo, bool update_viewport = true);
        glm::ivec2 currentFrameBufferSize() const;

        std::shared_ptr<GDeviceAPI> getDeviceImpl() const;
       
        GStates* getStates();

        ShaderProgram* getActiveProgram() const;
        FrameBufferPtr getActiveFrameBuffer() const;

        FrameBufferPtr createFrameBuffer();
        GPUTexture2DPtr createTexture2D();
        IndexBufferPtr createIndexBuffer();
        VertexBufferPtr createVertexBuffer();
        ShaderProgramPtr createShaderProgram();
        UniformBufferPtr createUniformBuffer();
        StructuredBufferPtr createStructuredBuffer();
        
        /*Texture3DPtr createTexture3D();*/

        void draw();

        void beginFrame();
        void endFrame();

        bool isSRGB() const;
        HWND getWindow() const;

    protected:
        bool createDefaultRTV();
        void setDefaultFramebuffer();
        void setViewport(const glm::vec2& size);
        void clearRenderTarget(const float* color = {}, bool clearDepth = true);
    protected:
        ShaderProgram* m_activeProgram = nullptr;
        std::weak_ptr<Framebuffer> m_activeFbo;
        Framebuffer* m_activeFboPtr = nullptr;
    private:
        glm::ivec2 getWindowSize() const;
        GSamplerState* obtainSampler(const Sampler& s);
    protected:
        std::shared_ptr<GDeviceAPI> m_device;
       
        WindowParameters m_params;
    };

    using GDevicePtr = std::shared_ptr<GDevice>;

    class DeviceHolder
    {
    protected:
        GDevicePtr m_device;
    public:
        DeviceHolder(const GDevicePtr& device);
        GDevicePtr getDevice();
    };

    enum class ShaderType { Vertex = 0, Hull = 1, Domain = 2, Geometry = 3, Pixel = 4, Compute = 5 };

    struct ShaderInput
    {
        std::wstring filePath;
        std::string target;
        std::string entyPoint;
        ShaderType type = ShaderType::Vertex;
    };

    enum class LayoutType { Byte, Word, UInt, Float };

    struct LayoutField
    {
        std::string name;
        LayoutType type = LayoutType::Byte;
        int num_fields = 0;
        bool do_norm = false;
        int offset = 0;
        int array_size = 0;
        int getSize() const;
        bool operator==(const LayoutField& l) const;
        std::size_t hash() const;
    };

    struct Layout
    {
        std::vector<LayoutField> fields;
        int stride;
        bool operator==(const Layout& l) const;
        std::size_t hash() const;
    };

    class ShaderProgram : public DeviceHolder
    {
    public:
        ShaderProgram(const GDevicePtr& device);
        ~ShaderProgram();

        virtual bool compileFromFile(const ShaderInput& input) = 0;
        virtual bool create() = 0;

        void activateProgram();
        void setInputBuffers(const VertexBufferPtr& vbo, const IndexBufferPtr& ibo, const VertexBufferPtr& instances, int instanceStepRate);

        void drawIndexed(PrimTopology pt, const DrawIndexedCmd& cmd);
        void drawIndexed(PrimTopology pt, const std::vector<DrawIndexedCmd>& cmd_buf);
        void drawIndexed(PrimTopology pt, int index_start = 0, int index_count = -1, int instance_count = -1, int base_vertex = 0, int base_instance = 0);
        void draw(PrimTopology pt, int vert_start = 0, int vert_count = -1, int instance_count = -1, int base_instance = 0);

        virtual void setValue(const char* name, float v) = 0;
        virtual void setValue(const char* name, int i) = 0;
        virtual void setValue(const char* name, const glm::vec2& v) = 0;
        virtual void setValue(const char* name, const glm::vec3& v) = 0;
        virtual void setValue(const char* name, const glm::vec4& v) = 0;
        virtual void setValue(const char* name, const glm::mat4& m) = 0;

        virtual void setResource(const char* name, const UniformBufferPtr& ubo) = 0;
        virtual void setResource(const char* name, const StructuredBufferPtr& sbo) = 0;
        virtual void setResource(const char* name, const GPUTexture2DPtr& tex, bool as_array = false, bool as_cubemap = false) = 0;
        //void setResource(const char* name, const Texture3DPtr& tex);
        virtual void setResource(const char* name, const Sampler& s) = 0;
    protected:
        const ShaderType cShaders[6] = { ShaderType::Vertex, ShaderType::Hull, ShaderType::Domain, ShaderType::Geometry, ShaderType::Pixel, ShaderType::Compute };

        enum class SlotKind { Uniform, Texture, Buffer, Sampler };

        struct ShaderSlot
        {
            SlotKind kind;
            std::string name;
            const Layout* layout;

            ShaderSlot() : kind(SlotKind::Uniform), layout(nullptr) {}
        };
    protected:
        void selectInputBuffers();
        void selectTopology(PrimTopology pt);

        bool isProgramActive() const;

        int obtainSlotIdx(SlotKind kind, const std::string& name, const Layout* layout);
        int findSlot(const char* name);
    protected:
        UniformBufferPtr m_ub[6];
        bool m_globals_dirty;

        std::array<std::string, 6> m_shaderCode = { std::string(), std::string(), std::string(), std::string(), std::string(), std::string() };

        std::vector<ShaderSlot> m_slots;
        VertexBufferPtr m_selectedVBO;
        IndexBufferPtr m_selectedIBO;
        VertexBufferPtr m_selectedInstances;
        int m_selectedInstanceStep;
    };

    class VertexBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
    public:
        VertexBuffer(const GDevicePtr& device);

        virtual void setState(const Layout* layout, int vertex_count, const void* data = nullptr);
        virtual void setSubData(int start_vertex, int num_vertices, const void* data) = 0;

        int getVertexCount() const;
        const Layout* getLayout() const;
    protected:
        const Layout* m_layout = nullptr;
        int m_vertCount = 0;
    };

    class IndexBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
    public:
        IndexBuffer(const GDevicePtr& device);

        virtual void setState(int ind_count, const void* data = nullptr);
        virtual void setSubData(int start_idx, int num_indices, const void* data) = 0;

        int getIndexCount() const;

    protected:
        int m_indCount = 0;
    };

    class StructuredBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
        friend class Framebuffer;
    public:
        StructuredBuffer(const GDevicePtr& device);

        virtual void setState(int stride, int vertex_count, bool UAV = false, bool UAV_with_counter = false, const void* data = nullptr) = 0;
        virtual void setSubData(int start_vertex, int num_vertices, const void* data) = 0;

        virtual void readBack(void* data) = 0;

        int getStride() const;
        int getVertexCount() const;
    protected:
        int m_stride = 0;
        int m_vert_count = 0;
        bool m_UAV_access = false;
        bool m_UAV_with_counter = false;
    };

    class LayoutSelector
    {
    public:
        virtual LayoutSelector* add(const std::string& name, LayoutType type, int num_fields, bool do_norm = true, int offset = -1, int array_size = 1) = 0;
        virtual const Layout* end(int stride_size = -1) = 0;
    };

    class LayoutSelectorInstance : public LayoutSelector
    {
    public:

        LayoutSelector* add(const std::string& name, LayoutType type, int num_fields, bool do_norm = true, int offset = -1, int array_size = 1) override
        {
            LayoutField f;
            f.name = name;
            f.type = type;
            f.num_fields = num_fields;
            f.do_norm = do_norm;
            f.offset = (offset < 0) ? m_curr_layout.stride : offset;
            f.array_size = array_size;
            m_curr_layout.fields.push_back(f);
            m_curr_layout.stride += f.getSize();
            return this;
        }

        const Layout* end(int stride_size = -1) override
        {
            if (stride_size > 0)
            {
                m_curr_layout.stride = stride_size;
            }

            auto it = m_cache.find(m_curr_layout);

            if (it == m_cache.end())
            {
                m_cache.insert({ m_curr_layout, std::make_unique<Layout>(m_curr_layout) });
                it = m_cache.find(m_curr_layout);
            }

            return it->second.get();
        }

        LayoutSelector* reset()
        {
            m_curr_layout.fields.clear();
            m_curr_layout.stride = 0;
            return this;
        };

    private:
        struct hash_fn
        {
            std::size_t operator() (const Layout& l) const
            {
                return l.hash();
            }
        };

    protected:
        std::unordered_map<Layout, std::unique_ptr<Layout>, hash_fn> m_cache;
        Layout m_curr_layout;
    };

    LayoutSelector* getLayoutSelector();

    class UniformBuffer : public DeviceHolder
    {
        friend class ShaderProgram;
    public:
        UniformBuffer(const GDevicePtr& device);
        
        virtual void setState(const Layout* layout, int elemets_count, const void* data = nullptr);
        virtual void setSubData(int start_element, int num_elements, const void* data);
        virtual void setValue(const char* name, float v, int element_idx = 0);
        virtual void setValue(const char* name, int i, int element_idx = 0);
        virtual void setValue(const char* name, const glm::vec2& v, int element_idx = 0);
        virtual void setValue(const char* name, const glm::vec3& v, int element_idx = 0);
        virtual void setValue(const char* name, const glm::vec4& v, int element_idx = 0);
        virtual void setValue(const char* name, const glm::mat4& m, int element_idx = 0);
        virtual void validateDynamicData();
       
        const Layout* getLayout() const;

    protected:
        void setValue(void* dest, const void* data, int datasize);
        void* find(const char* name, int element_idx);
    protected:
        std::vector<char> m_data;
        const Layout* m_layout;
        int m_elements_count;
        bool m_dirty = false;
    };

    class GPUTexture2D : public DeviceHolder 
    {
        friend class Framebuffer;
        friend class ShaderProgram;   
    public:
        GPUTexture2D(const GDevicePtr& device);

        virtual void setState(TextureFmt fmt, int mip_levels = 0) = 0;
        virtual void setState(TextureFmt fmt, glm::ivec2 size, int mip_levels = 0, int slices = 1, const void* data = nullptr) = 0;
        virtual void setSubData(const glm::ivec2& offset, const glm::ivec2& size, int slice, int mip, const void* data) = 0;
        virtual void generateMips() = 0;

        virtual void readBack(void* data, int mip, int array_slice) = 0;

        TextureFmt format() const;
        glm::ivec2 size() const;
        int slicesCount() const;
        int mipsCount() const;
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
    protected:        
        TextureFmt m_fmt;
        glm::ivec2 m_size;
        int m_slices;
        int m_mips_count;
    };

    class Framebuffer : public DeviceHolder
    {
        friend class GDevice;
    protected:
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
    public:
        Framebuffer(const GDevicePtr& device);
        ~Framebuffer();

        virtual void clearColorSlot(int slot, const glm::vec4& color) = 0;
        virtual void clearDS(float depth, bool clear_depth = true, char stencil = 0, bool clear_stencil = false) = 0;

        virtual void setColorSlot(int slot, const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1) = 0;
        virtual void setDS(const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1, bool readonly = false) = 0;
        
        GPUTexture2DPtr getColorSlot(int slot) const;
        GPUTexture2DPtr getDS() const;

        virtual void clearUAV(int slot, uint32_t v) = 0;
        virtual void setUAV(int slot, const GPUTexture2DPtr& tex, int mip = 0, int slice_start = 0, int slice_count = 1, bool as_array = false) = 0;
        virtual void setUAV(int slot, const StructuredBufferPtr& buf, int initial_counter = -1) = 0;

        virtual void blitToDefaultFBO(int from_slot) = 0;

        void setSizeFromWindow();
        virtual void setSize(const glm::ivec2& xy) = 0;
        glm::ivec2 getSize() const;
    protected:
        virtual void prepareSlots() = 0;
    protected:        
        GPUTexture2DPtr m_tex[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        GPUTexture2DPtr m_depth;

        Tex2DParams m_tex_params[G_D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
        Tex2DParams m_depth_params;

        std::vector<UINT> m_uav_initial_counts;

        glm::ivec2 m_size{};
        int m_rtv_count = 0;
        int m_uav_to_bind_count = 0;

        bool m_colors_to_bind_dirty = false;
    };
}
