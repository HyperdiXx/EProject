#include "egapi.h"

#include "edx11api.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace EProject
{   
    GDevice::GDevice(HWND wnd, bool sRGB)
    {
        RECT rct;
        GetClientRect(wnd, &rct);

        m_params.hwnd = wnd;
        m_params.name = "Window1";
        m_params.isSrgb = sRGB;
        m_params.size = glm::ivec2(rct.right - rct.left, rct.bottom - rct.top);

        m_device = std::make_shared<DX11GDevice>(shared_from_this());
        m_device->init(m_params);
    }

    GDevice::~GDevice()
    {
    }

    FrameBufferPtr GDevice::setFrameBuffer(const FrameBufferPtr& fbo, bool update_viewport)
    {
        FrameBufferPtr currentFbo = m_activeFbo.lock();
        //std::weak_ptr<Framebuffer> m_new_fbo = fbo;

        if (m_activeFboPtr != fbo.get())
        {
            //m_activeFbo = m_new_fbo;
            m_activeFboPtr = fbo.get();

            if (m_activeFboPtr)
            {
                m_activeFboPtr->prepareSlots();
                /*m_context->OMSetRenderTargetsAndUnorderedAccessViews(
                    UINT(m_activeFboPtr->m_rtv_count),
                    m_activeFboPtr->m_colors_to_bind.data(),
                    m_activeFboPtr->m_depth_view.Get(),
                    UINT(m_activeFboPtr->m_rtv_count),
                    UINT(glm::clamp<int>(int(m_activeFboPtr->m_uav_to_bind.size()) - m_activeFboPtr->m_rtv_count, 0, 7)),
                    m_activeFboPtr->m_uav_to_bind.data(),
                    m_activeFboPtr->m_uav_initial_counts.data()
                );*/
            }
            else
            {
                setDefaultFramebuffer();
            }
        }
        
        if (update_viewport)
        {
            setViewport(currentFrameBufferSize());
        }

        return currentFbo;
    }

    GSamplerState* GDevice::obtainSampler(const Sampler& s)
    {        
        return m_device->obtainSamplerState(s);
    }

    glm::ivec2 GDevice::currentFrameBufferSize() const
    {
        return m_params.size;
    }

    std::shared_ptr<GDeviceAPI> GDevice::getDeviceImpl() const
    {
        return m_device;
    }

    GStates* GDevice::getStates()
    {
        return m_device->getStates();
    }

    FrameBufferPtr GDevice::getActiveFrameBuffer() const
    {
        return m_activeFbo.lock();
    }

    ShaderProgram* GDevice::getActiveProgram() const
    {
        return m_activeProgram;
    }

    FrameBufferPtr GDevice::createFrameBuffer()
    {
        return m_device->createFramebuffer();
    }

    GPUTexture2DPtr GDevice::createTexture2D()
    {
        return m_device->createTexture2D();
    }

    IndexBufferPtr GDevice::createIndexBuffer()
    {
        return m_device->createIndexBuffer();
    }

    VertexBufferPtr GDevice::createVertexBuffer()
    {
        return m_device->createVertexBuffer();
    }

    ShaderProgramPtr GDevice::createShaderProgram()
    {
        return m_device->createShaderProgram();
    }

    UniformBufferPtr GDevice::createUniformBuffer()
    {
        return m_device->createUniformBuffer();
    }

    StructuredBufferPtr GDevice::createStructuredBuffer()
    {
        return m_device->createStructuredBuffer();
    }

    bool GDevice::createDefaultRTV()
    {     
        return true;
        //return m_device->createDefaultRTV(m_params);
    }

    void GDevice::beginFrame()
    {
        const glm::ivec2 new_wnd_size = getWindowSize();

        if (m_params.size != new_wnd_size)
        {
            m_params.size = new_wnd_size;

            createDefaultRTV();
        }

        setDefaultFramebuffer();
        setViewport(m_params.size);

        const float clearColor[4] = {0.75f, 0.75f, 0.75f, 1.0f};
        clearRenderTarget(clearColor, true);        
    }

    void GDevice::endFrame()
    {
        m_device->endFrame();        
    }

    bool GDevice::isSRGB() const
    {
        return m_params.isSrgb;
    }

    HWND GDevice::getWindow() const
    {
        return m_params.hwnd;
    }

    glm::ivec2 GDevice::getWindowSize() const
    {
        RECT rct;
        GetClientRect(m_params.hwnd, &rct);
        return glm::ivec2(rct.right - rct.left, rct.bottom - rct.top);
    }

    void GDevice::setDefaultFramebuffer()
    {
        m_device->setDefaultFramebuffer();      
    }

    void GDevice::setViewport(const glm::vec2& size)
    {
        m_device->setViewport(size);
    }

    void GDevice::clearRenderTarget(const float* color, bool clearDepth)
    {
        m_device->clearRenderTarget(color, clearDepth);
    }

    ShaderProgram::ShaderProgram(const GDevicePtr& device) : DeviceHolder(device)
    {
        m_globals_dirty = false;
        m_selectedInstanceStep = 0;
    }

    ShaderProgram::~ShaderProgram()
    {
        if (m_device->m_activeProgram == this) m_device->m_activeProgram = nullptr;
    }

    bool ShaderProgram::compileFromFile(const ShaderInput& input)
    {



        return true;
    }

    bool ShaderProgram::create()
    {           
        return true;
    }

    void ShaderProgram::activateProgram()
    {
        if (m_globals_dirty)
        {
            for (int i = 0; i < 6; i++)
            {
                if (m_ub[i])
                {
                    m_ub[i]->validateDynamicData();
                }
            }
        }

        if (!isProgramActive()) 
        {
            m_device->m_activeProgram = this;
            
            for (const auto& slot : m_slots)
            {
                //slot.select(m_device->getDX11DeviceContext());
            }
                        
            selectInputBuffers();

            /*ID3D11DeviceChild* tmp = nullptr;
            tmp = m_shaders[int(ShaderType::Vertex)] ? m_shaders[int(ShaderType::Vertex)].Get() : nullptr;
            m_device->getDX11DeviceContext()->VSSetShader((ID3D11VertexShader*)tmp, nullptr, 0);
            tmp = m_shaders[int(ShaderType::Hull)] ? m_shaders[int(ShaderType::Hull)].Get() : nullptr;
            m_device->getDX11DeviceContext()->HSSetShader((ID3D11HullShader*)tmp, nullptr, 0);
            tmp = m_shaders[int(ShaderType::Domain)] ? m_shaders[int(ShaderType::Domain)].Get() : nullptr;
            m_device->getDX11DeviceContext()->DSSetShader((ID3D11DomainShader*)tmp, nullptr, 0);
            tmp = m_shaders[int(ShaderType::Geometry)] ? m_shaders[int(ShaderType::Geometry)].Get() : nullptr;
            m_device->getDX11DeviceContext()->GSSetShader((ID3D11GeometryShader*)tmp, nullptr, 0);
            tmp = m_shaders[int(ShaderType::Pixel)] ? m_shaders[int(ShaderType::Pixel)].Get() : nullptr;
            m_device->getDX11DeviceContext()->PSSetShader((ID3D11PixelShader*)tmp, nullptr, 0);
            tmp = m_shaders[int(ShaderType::Compute)] ? m_shaders[int(ShaderType::Compute)].Get() : nullptr;
            m_device->getDX11DeviceContext()->CSSetShader((ID3D11ComputeShader*)tmp, nullptr, 0);*/
        }
    }

    void ShaderProgram::setInputBuffers(const VertexBufferPtr& vbo, const IndexBufferPtr& ibo, const VertexBufferPtr& instances, int instanceStepRate)
    {
        m_selectedVBO = vbo;
        m_selectedIBO = ibo;
        m_selectedInstances = instances;
        m_selectedInstanceStep = instanceStepRate;
        if (isProgramActive())
        {
            selectInputBuffers();
        }
    }

    void ShaderProgram::drawIndexed(PrimTopology pt, const DrawIndexedCmd& cmd)
    {
    }

    void ShaderProgram::drawIndexed(PrimTopology pt, const std::vector<DrawIndexedCmd>& cmd_buf)
    {
    }

    void ShaderProgram::drawIndexed(PrimTopology pt, int index_start, int index_count, int instance_count, int base_vertex, int base_instance)
    {
        activateProgram();
        selectTopology(pt);
                
        m_device->getStates()->validateStates();

        if (index_count < 0) index_count = m_selectedIBO->getIndexCount();
        //if (instance_count < 0) instance_count = m_selected_instances ? m_selected_instances->VertexCount() : 0;
        if (instance_count < 0) instance_count = 0;

        //m_device->draw();

        if (instance_count)
        {
            //m_device->getDX11DeviceContext()->DrawIndexedInstanced(index_count, instance_count, index_start, base_vertex, base_instance);
        }
        else
        {
            //m_device->getDX11DeviceContext()->DrawIndexed(index_count, index_start, base_vertex);
        }
    }

    void ShaderProgram::draw(PrimTopology pt, int vert_start, int vert_count, int instance_count, int base_instance)
    {
        activateProgram();
        selectTopology(pt);
        
        m_device->getStates()->validateStates();
        
        //if (instance_count < 0) instance_count = m_selected_instances ? m_selected_instances->VertexCount() : 0;

        if (vert_count < 0) vert_count = m_selectedVBO->getVertexCount();
        if (instance_count < 0) instance_count = 0;

        if (instance_count)
        {
            //m_device->getDX11DeviceContext()->DrawInstanced(vert_count, instance_count, vert_start, base_instance);
        }
        else 
        {
            //m_device->getDX11DeviceContext()->Draw(vert_count, vert_start);
        }
    }

    void ShaderProgram::setValue(const char* name, float v)
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_ub[i])
            {
                m_ub[i]->setValue(name, v);
            }
        }

        m_globals_dirty = true;
    }

    void ShaderProgram::setValue(const char* name, int i)
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_ub[i])
            {
                m_ub[i]->setValue(name, i);
            }
        }

        m_globals_dirty = true;
    }

    void ShaderProgram::setValue(const char* name, const glm::vec2& v)
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_ub[i])
            {
                m_ub[i]->setValue(name, v);
            }
        }

        m_globals_dirty = true;
    }

    void ShaderProgram::setValue(const char* name, const glm::vec3& v)
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_ub[i])
            {
                m_ub[i]->setValue(name, v);
            }
        }

        m_globals_dirty = true;
    }

    void ShaderProgram::setValue(const char* name, const glm::vec4& v)
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_ub[i])
            {
                m_ub[i]->setValue(name, v);
            }
        }

        m_globals_dirty = true;
    }

    void ShaderProgram::setValue(const char* name, const glm::mat4& m)
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_ub[i])
            {
                m_ub[i]->setValue(name, m);
            }
        }

        m_globals_dirty = true;
    }

    void ShaderProgram::setResource(const char* name, const UniformBufferPtr& ubo)
    {
        int idx = findSlot(name);
        if (idx < 0)
        {
            return;
        }
        
        ShaderSlot& slot = m_slots[idx];
        /*if ((slot.buffer ? slot.buffer.Get() : nullptr) != (ubo ? ubo->m_handle.Get() : nullptr))
        {
            slot.buffer = ubo ? ubo->m_handle : nullptr;
            if (isProgramActive())
            {
                slot.select(m_device->getDX11DeviceContext());
            }
        }*/
    }

    void ShaderProgram::selectInputBuffers()
    {

    }

    void ShaderProgram::selectTopology(PrimTopology pt)
    {
        
    }

    bool ShaderProgram::isProgramActive() const
    {
        return m_device->m_activeProgram == this;
    }

    int ShaderProgram::obtainSlotIdx(SlotKind kind, const std::string& name, const Layout* layout)
    {
        if (name != "Globals")
        {
            for (size_t i = 0; i < m_slots.size(); i++) 
            {
                if (m_slots[i].name == name)
                {
                    assert(m_slots[i].kind == kind);
                    assert(m_slots[i].layout == layout);
                    return static_cast<int>(i);
                }
            }
        }
        
        ShaderSlot newSlot;
        newSlot.kind = kind;
        newSlot.name = name;
        newSlot.layout = layout;
        m_slots.push_back(newSlot);
        
        return static_cast<int>(m_slots.size() - 1);
    }

    int ShaderProgram::findSlot(const char* name)
    {
        for (size_t i = 0; i < m_slots.size(); i++)
        {
            if (m_slots[i].name == name)
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    DeviceHolder::DeviceHolder(const GDevicePtr& device) : m_device(device)
    {

    }

    GDevicePtr DeviceHolder::getDevice()
    {
        return m_device;
    }

    VertexBuffer::VertexBuffer(const GDevicePtr& device) : DeviceHolder(device)
    {
        m_vertCount = 0;
        m_layout = nullptr;
    }

    void VertexBuffer::setState(const Layout* layout, int vertex_count, const void* data)
    {
        m_layout = layout;
        m_vertCount = vertex_count;
    }

    int VertexBuffer::getVertexCount() const
    {
        return m_vertCount;
    }

    const Layout* VertexBuffer::getLayout() const
    {
        return m_layout;
    }

    IndexBuffer::IndexBuffer(const GDevicePtr& device) : DeviceHolder(device)
    {
        m_indCount = 0;
    }

    void IndexBuffer::setState(int ind_count, const void* data)
    {
        m_indCount = ind_count;
    }

    int IndexBuffer::getIndexCount() const
    {
        return m_indCount;
    }

    int LayoutField::getSize() const
    {
        switch (type)
        {
        case LayoutType::Byte: return 1 * num_fields * array_size;
        case LayoutType::Word: return 2 * num_fields * array_size;
        case LayoutType::UInt: return 4 * num_fields * array_size;
        case LayoutType::Float: return 4 * num_fields * array_size;
        default:
            assert(false);
        }
        return 0;
    }

    bool LayoutField::operator==(const LayoutField& l) const
    {
        return  (name == l.name) &&
                (type == l.type) &&
                (num_fields == l.num_fields) &&
                (do_norm == l.do_norm) &&
                (offset == l.offset) &&
                (array_size == l.array_size);
    }

    std::size_t LayoutField::hash() const
    {
        return  std::hash<std::string>()(name) ^
                std::hash<int>()(num_fields) ^
                std::hash<bool>()(do_norm) ^
                std::hash<int>()(offset) ^
                std::hash<int>()(array_size) ^
                std::hash<LayoutType>()(type);
    }


    bool Layout::operator==(const Layout& l) const
    {
        if (fields.size() != l.fields.size()) 
            return false;
        
        if (stride != l.stride) 
            return false;
        
        for (size_t i = 0; i < fields.size(); i++) 
        {
            if (!(fields[i] == l.fields[i])) return false;
        }
       
        return true;
    }

    std::size_t Layout::hash() const
    {
        std::size_t n = std::hash<int>()(stride);

        for (size_t i = 0; i < fields.size(); i++) {
            n ^= fields[i].hash();
        }
        return n;
    }

    LayoutSelectorInstance globalLS;
    LayoutSelector* getLayoutSelector()
    {
        return globalLS.reset();
    }

    UniformBuffer::UniformBuffer(const GDevicePtr& device) : DeviceHolder(device)
    {
        m_elements_count = 0;
        m_layout = nullptr;
        m_dirty = false;
    }

    void UniformBuffer::setValue(void* dest, const void* data, int datasize)
    {
        memcpy(dest, data, datasize);
        m_dirty = true;
    }

    void* UniformBuffer::find(const char* name, int element_idx)
    {
        for (const auto& f : m_layout->fields)
        {
            if (f.name == name)
            {
                int offset = f.offset + m_layout->stride * element_idx;
                return &m_data[offset];
            }
        }

        return nullptr;
    }

    void UniformBuffer::setState(const Layout* layout, int elemets_count, const void* data)
    {
        m_layout = layout;
        m_elements_count = elemets_count;
        m_data.resize(static_cast<size_t>(layout->stride) * elemets_count);
        assert(m_data.size());
        if (data)
        {
            memcpy(m_data.data(), data, m_data.size());
        }

        
        
        m_dirty = false;
    }

    void UniformBuffer::setSubData(int start_element, int num_elements, const void* data)
    {
        memcpy(&m_data[static_cast<size_t>(m_layout->stride) * start_element], data, static_cast<size_t>(m_layout->stride) * num_elements);
        m_dirty = true;
    }

    void UniformBuffer::setValue(const char* name, float v, int element_idx)
    {
        void* dst = find(name, element_idx);
        if (dst)
        {
            setValue(dst, &v, sizeof(v));
        }
    }

    void UniformBuffer::setValue(const char* name, int i, int element_idx)
    {
        void* dst = find(name, element_idx);
        if (dst)
        {
            setValue(dst, &i, sizeof(i));
        }
    }

    void UniformBuffer::setValue(const char* name, const glm::vec2& v, int element_idx)
    {
        void* dst = find(name, element_idx);
        if (dst)
        {
            setValue(dst, &v, sizeof(v));
        }
    }

    void UniformBuffer::setValue(const char* name, const glm::vec3& v, int element_idx)
    {
        void* dst = find(name, element_idx);
        if (dst)
        {
            setValue(dst, &v, sizeof(v));
        }
    }

    void UniformBuffer::setValue(const char* name, const glm::vec4& v, int element_idx)
    {
        void* dst = find(name, element_idx);
        if (dst)
        {
            setValue(dst, &v, sizeof(v));
        }
    }

    void UniformBuffer::setValue(const char* name, const glm::mat4& m, int element_idx)
    {
        void* dst = find(name, element_idx);
        if (dst)
        {
            setValue(dst, &m, sizeof(m));
        }
    }

    void UniformBuffer::validateDynamicData()
    {
        if (!m_dirty)
        {
            return;
        }
        
        m_dirty = false;

        
    }

    const Layout* UniformBuffer::getLayout() const
    {
        return m_layout;
    }

    StructuredBuffer::StructuredBuffer(const GDevicePtr& device) : DeviceHolder(device)
    {
    }

    void StructuredBuffer::setState(int stride, int vertex_count, bool UAV, bool UAV_with_counter, const void* data)
    {
        
    }

    void StructuredBuffer::setSubData(int start_vertex, int num_vertices, const void* data)
    {
       
    }

    int StructuredBuffer::getStride() const
    {
        return m_stride;
    }

    int StructuredBuffer::getVertexCount() const
    {
        return m_vert_count;
    }

    GPUTexture2D::GPUTexture2D(const GDevicePtr& device) : DeviceHolder(device)
    {
        m_fmt = TextureFmt::RGBA8;
        m_size = glm::ivec2(0, 0);
        m_slices = 1;
        m_mips_count = 1;
    }

    TextureFmt GPUTexture2D::format() const
    {
        return m_fmt;
    }

    glm::ivec2 GPUTexture2D::size() const
    {
        return m_size;
    }

    int GPUTexture2D::slicesCount() const
    {
        return m_slices;
    }

    int GPUTexture2D::mipsCount() const
    {
        return m_mips_count;
    }

    Framebuffer::Framebuffer(const GDevicePtr& device) : DeviceHolder(device)
    {
    }

    Framebuffer::~Framebuffer()
    {
        if (m_device->m_activeFboPtr == this)
        {
            m_device->setFrameBuffer(nullptr);
        }
    }

    GPUTexture2DPtr Framebuffer::getColorSlot(int slot) const
    {
        return m_tex[slot];
    }

    GPUTexture2DPtr Framebuffer::getDS() const
    {
        return m_depth;
    }

    void Framebuffer::setSizeFromWindow()
    {
        RECT rct;
        GetClientRect(m_device->m_params.hwnd, &rct);
        setSize(glm::ivec2(rct.right - rct.left, rct.bottom - rct.top));
    }

    glm::ivec2 Framebuffer::getSize() const
    {
        return m_size;
    }

    Framebuffer::Tex2DParams::Tex2DParams()
    {
        mip = 0;
        slice_start = 0;
        slice_count = 0;
        read_only = false;
        as_array = false;
    }
    
    Framebuffer::Tex2DParams::Tex2DParams(int m, int s_start, int s_count, bool ronly, bool as_array)
    {
        mip = m;
        slice_start = s_start;
        slice_count = s_count;
        read_only = ronly;
        this->as_array = as_array;
    }

    bool Framebuffer::Tex2DParams::operator==(const Tex2DParams& b)
    {
        return (mip == b.mip) && (slice_start == b.slice_start) && (slice_count == b.slice_count) && (read_only == b.read_only);
    }
}