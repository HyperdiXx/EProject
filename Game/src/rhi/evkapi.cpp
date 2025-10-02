#include "rhi/evkapi.h"

namespace EProject
{
    void VkGDevice::init(const WindowParameters& params)
    {
        
    }
    
    void VkGDevice::shutdown()
    {

    }

    FrameBufferPtr VkGDevice::createFramebuffer()
    {
        return {};
    }
    
    GPUTexture2DPtr VkGDevice::createTexture2D()
    {
        return {};
    }

    IndexBufferPtr VkGDevice::createIndexBuffer()
    {
        return {};
    }

    VertexBufferPtr VkGDevice::createVertexBuffer()
    {
        return {};
    }

    ShaderProgramPtr VkGDevice::createShaderProgram()
    {
        return {};
    }
    
    UniformBufferPtr VkGDevice::createUniformBuffer()
    {
        return {};
    }

    StructuredBufferPtr VkGDevice::createStructuredBuffer()
    {
        return {};
    }

    void VkGDevice::endFrame()
    {

    }

    void VkGDevice::draw(int vert_start, int vert_count, int instance_count, int base_instance)
    {

    }

    void VkGDevice::drawIndexed(int index_start, int index_count, int instance_count, int base_vertex, int base_instance)
    {

    }

    GDeviceAPI* VkGDevice::getDevicePtrRaw()
    {
        return nullptr;
    }

    GSamplerState* VkGDevice::obtainSamplerState(const Sampler& s)
    {
        return nullptr;
    }

    GStates* VkGDevice::getStates()
    {
        return nullptr;
    }

    bool VkGDevice::createDefaultRTV(const WindowParameters& params)
    {
        return true;
    }

    void VkGDevice::setDefaultFramebuffer()
    {

    }

    void VkGDevice::setViewport(const glm::vec2& size)
    {

    }

    void VkGDevice::clearRenderTarget(const float* color, bool clearDepth)
    {

    }
}