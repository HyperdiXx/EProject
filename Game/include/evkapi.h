#pragma once

#include <egapi.h>

#include <vulkan/vulkan.h>

namespace EProject
{
    class VkGDevice : public GDeviceAPI
    {
    public:
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

    private:
        VkInstance vk_instance = VK_NULL_HANDLE;
        std::vector<const char*> supportedInstanceExtensions;
    };
}
