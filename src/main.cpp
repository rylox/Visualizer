#include <iostream>
#include <set>

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include "../external/rtaudio/RtAudio.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

bool checkLayers(std::vector<char const *> const &layers, std::vector<vk::LayerProperties> const &properties) {
// return true if all layers are listed in the properties
    for (const char *layerName: layers) {
        bool layerFound = false;
        for (const auto &layerProperties: properties) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) return false;
    }
    return true;
}

bool checkExtensions(std::vector<char const *> const &extensions,
                     std::vector<vk::ExtensionProperties> const &properties) {
// return true if all extensions are listed in the properties
    for (const char *extensionName: extensions) {
        bool extensionFound = false;
        for (const auto &extensionProperties: properties) {
            if (strcmp(extensionName, extensionProperties.extensionName) == 0) {
                extensionFound = true;
                break;
            }
        }
        if (!extensionFound) return false;
    }
    return true;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(VkInstance instance,
                                                              const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                              const VkAllocationCallbacks *pAllocator,
                                                              VkDebugUtilsMessengerEXT *pMessenger) {

    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                           "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(VkInstance instance,
                                                           VkDebugUtilsMessengerEXT messenger,
                                                           VkAllocationCallbacks const *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                            "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, messenger, pAllocator);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                             VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                             VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                             void * /*pUserData*/ ) {
    std::cout << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() const {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats) {
    if (availableFormats.size() == 1 && availableFormats[0].format == vk::Format::eUndefined) {
        return {vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear};
    }

    for (const auto &availableFormat: availableFormats) {
        if (availableFormat.format == vk::Format::eB8G8R8A8Unorm &&
            availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes) {
    vk::PresentModeKHR bestMode = vk::PresentModeKHR::eFifo;

    for (const auto &availablePresentMode: availablePresentModes) {
        if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
            return availablePresentMode;
        } else if (availablePresentMode == vk::PresentModeKHR::eImmediate) {
            bestMode = availablePresentMode;
        }
    }

    return bestMode;
}

vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        vk::Extent2D actualExtent = {static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT)};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

static std::vector<char> readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData )
{
    if ( status )
        std::cout << "Stream overflow detected!" << std::endl;
    // Do something with the data in the "inputBuffer" buffer.

    return 0;
}


int main() {

    RtAudio audio;
    // Determine the number of devices available
    unsigned int devices = audio.getDeviceCount();
    // Scan through devices for various capabilities
    RtAudio::DeviceInfo info;
    for ( unsigned int i=0; i<devices; i++ ) {
        info = audio.getDeviceInfo( i );
        if ( info.probed == true ) {
            // Print, for example, the maximum number of output channels for each device
            std::cout << "device = " << i << " " << info.name << " " << "default In: " << info.isDefaultInput
            << " default Out: " << info.isDefaultOutput;
            std::cout << ": maximum output channels = " << info.outputChannels << "\n";
        }
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = audio.getDefaultInputDevice();
    parameters.nChannels = 2;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256; // 256 sample frames

    audio.openStream( NULL, &parameters, RTAUDIO_SINT16,
                    sampleRate, &bufferFrames, &record );
    audio.startStream();

    if (!glfwInit()) //Initialize GLFW
    {
        std::cout << "GLFW not initialized." << std::endl;
        abort();
    }
    if (!glfwVulkanSupported()) //Any Vulkan-related function requires GLFW initialized
    {
        std::cout << "Vulkan not supported." << std::endl;
        abort();
    }

    /* Create an instance */
    uint32_t ext_count; // an output placeholder
    char const **ext_list = glfwGetRequiredInstanceExtensions(&ext_count);

    std::vector<const char *> requiredExtensions(ext_list, ext_list + ext_count);
    std::vector<vk::ExtensionProperties> instanceExtensions = vk::enumerateInstanceExtensionProperties();

    std::cout << "available instance extensions:" << std::endl;
    for (auto const &extension: instanceExtensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }

    requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    std::cout << "required extensions:" << std::endl;
    for (auto const &extension: requiredExtensions) { //on Windows, ext_count >=2
        std::cout << '\t' << extension << std::endl;
    }

    if (!checkExtensions(requiredExtensions, instanceExtensions))
        std::cout << "Extensions unavailable." << std::endl;

    std::vector<vk::LayerProperties> instanceLayers = vk::enumerateInstanceLayerProperties();
    std::vector<const char *> requiredLayers = {"VK_LAYER_KHRONOS_validation"};

    if (!checkLayers(requiredLayers, instanceLayers))
        std::cout << "Layers unavailable." << std::endl;

    vk::InstanceCreateInfo instanceCreateInfo{vk::InstanceCreateFlags(),
                                              nullptr,
                                              static_cast<uint32_t>(requiredLayers.size()),
                                              requiredLayers.data(),
                                              static_cast<uint32_t>(requiredExtensions.size()),
                                              requiredExtensions.data()

    };
    vk::UniqueInstance instance = vk::createInstanceUnique(instanceCreateInfo);

    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(//vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                                       vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                                                       vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

    vk::DebugUtilsMessengerCreateInfoEXT debugInfo{vk::DebugUtilsMessengerCreateFlagsEXT(),
                                                   severityFlags,
                                                   messageTypeFlags,
                                                   &debugCallback
    };

    vk::UniqueDebugUtilsMessengerEXT debugUtilsMessenger = instance->createDebugUtilsMessengerEXTUnique(debugInfo);

    /* Create a Window and a Surface */
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow *hWnd = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    VkSurfaceKHR surface;
    glfwCreateWindowSurface(*instance, hWnd, nullptr, &surface);
    vk::UniqueSurfaceKHR uniqueSurface = vk::UniqueSurfaceKHR(surface);

    /* Get Physical Devices */
    std::vector<vk::PhysicalDevice> physicalDevices = instance->enumeratePhysicalDevices();

    std::cout << "Available Physical Devices:" << std::endl;
    for (const auto &physicalDevice: physicalDevices) {
        std::cout << "\t" << physicalDevice.getProperties().deviceName << std::endl;
    }

    auto physicalDevice = physicalDevices.front();

    // get all queues of the chosen PhysicalDevice
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

    // get the indices of the required queues
    QueueFamilyIndices indices;

    int i = 0;
    for (const auto &queueFamily: queueFamilyProperties) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
            indices.graphicsFamily = i;
        }

        if (queueFamily.queueCount > 0 && physicalDevice.getSurfaceSupportKHR(i, surface)) {
            indices.presentFamily = i;
        }
        if (indices.isComplete()) break;

        i++;
    }

    std::vector<vk::DeviceQueueCreateInfo> deviceQueueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily: uniqueQueueFamilies) {
        deviceQueueCreateInfos.emplace_back(
                vk::DeviceQueueCreateFlags(),
                queueFamily,
                1, // queueCount
                &queuePriority
        );
    }

    auto deviceFeatures = vk::PhysicalDeviceFeatures();
    auto deviceCreateInfo = vk::DeviceCreateInfo(
            vk::DeviceCreateFlags(),
            static_cast<uint32_t>(deviceQueueCreateInfos.size()),
            deviceQueueCreateInfos.data()
    );

    const std::vector<const char *> requiredDeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t> (requiredDeviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();

    /* Modern Vulkan makes no distinction between instance and device specific validation layers.
     * Still a good Idea to implement it for better backwards capabilities.
     */
    deviceCreateInfo.enabledLayerCount = static_cast<uint32_t> (requiredLayers.size());
    deviceCreateInfo.ppEnabledLayerNames = requiredLayers.data();

    vk::UniqueDevice device = physicalDevice.createDeviceUnique(deviceCreateInfo);

    auto hGraphicsQ = device->getQueue(indices.graphicsFamily.value(), 0);
    auto hPresentQ = device->getQueue(indices.presentFamily.value(), 0);

    SwapChainSupportDetails swapChainDetails{physicalDevice.getSurfaceCapabilitiesKHR(*uniqueSurface),
                                             physicalDevice.getSurfaceFormatsKHR(*uniqueSurface),
                                             physicalDevice.getSurfacePresentModesKHR(*uniqueSurface)
    };

    vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainDetails.formats);
    vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainDetails.presentModes);
    vk::Extent2D extent = chooseSwapExtent(swapChainDetails.capabilities);

    uint32_t imageCount = swapChainDetails.capabilities.minImageCount + 1;
    if (swapChainDetails.capabilities.maxImageCount > 0 && imageCount > swapChainDetails.capabilities.maxImageCount) {
        imageCount = swapChainDetails.capabilities.maxImageCount;
    }

    vk::SwapchainCreateInfoKHR swapChainCreateInfo(
            vk::SwapchainCreateFlagsKHR(),
            *uniqueSurface,
            imageCount,
            surfaceFormat.format,
            surfaceFormat.colorSpace,
            extent,
            1, // imageArrayLayers
            vk::ImageUsageFlagBits::eColorAttachment
    );

    std::vector<uint32_t> queueFamilyIndices = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        swapChainCreateInfo.imageSharingMode = vk::SharingMode::eConcurrent;
        swapChainCreateInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size());
        swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    } else {
        swapChainCreateInfo.imageSharingMode = vk::SharingMode::eExclusive;
    }

    swapChainCreateInfo.preTransform = swapChainDetails.capabilities.currentTransform;
    swapChainCreateInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    swapChainCreateInfo.presentMode = presentMode;
    swapChainCreateInfo.clipped = VK_TRUE;

    swapChainCreateInfo.oldSwapchain = vk::SwapchainKHR(nullptr);

    auto swapChain = device->createSwapchainKHR(swapChainCreateInfo);

    auto swapChainImages = device->getSwapchainImagesKHR(swapChain);

    auto swapChainImageFormat = surfaceFormat.format;
    auto swapChainExtent = extent;

    std::vector<vk::ImageView> swapChainImageViews;

    swapChainImageViews.resize(swapChainImages.size());
    for (size_t j = 0; j < swapChainImages.size(); j++) {
        vk::ImageViewCreateInfo createInfo = {};
        createInfo.image = swapChainImages[j];
        createInfo.viewType = vk::ImageViewType::e2D;
        createInfo.format = swapChainImageFormat;
        createInfo.components.r = vk::ComponentSwizzle::eIdentity;
        createInfo.components.g = vk::ComponentSwizzle::eIdentity;
        createInfo.components.b = vk::ComponentSwizzle::eIdentity;
        createInfo.components.a = vk::ComponentSwizzle::eIdentity;
        createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        swapChainImageViews[j] = device->createImageView(createInfo);
    }

    auto vertShaderCode = readFile("shaders/shader.vert.spv");
    auto fragShaderCode = readFile("shaders/shader.frag.spv");

    auto vertexShaderModule = device->createShaderModuleUnique({
                                                                       vk::ShaderModuleCreateFlags(),
                                                                       vertShaderCode.size(),
                                                                       reinterpret_cast<const uint32_t *>(vertShaderCode.data())
                                                               });

    auto fragmentShaderModule = device->createShaderModuleUnique({
                                                                         vk::ShaderModuleCreateFlags(),
                                                                         fragShaderCode.size(),
                                                                         reinterpret_cast<const uint32_t *>(fragShaderCode.data())
                                                                 });

    std::vector<vk::PipelineShaderStageCreateInfo> pipelineShaderStageCreateInfos = {
            vk::PipelineShaderStageCreateInfo(
                    vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eVertex, *vertexShaderModule,
                    "main"),
            vk::PipelineShaderStageCreateInfo(
                    vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eFragment, *fragmentShaderModule,
                    "main")
    };

    vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo(
            vk::PipelineVertexInputStateCreateFlags(),  // flags
            nullptr,                                    // vertexBindingDescriptions
            nullptr                                     // vertexAttributeDescriptions
    );

    vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
            vk::PipelineInputAssemblyStateCreateFlags(), vk::PrimitiveTopology::eTriangleList);

    vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
            vk::PipelineViewportStateCreateFlags(), 1, nullptr, 1, nullptr);

    vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
            vk::PipelineRasterizationStateCreateFlags(),  // flags
            false,                                        // depthClampEnable
            false,                                        // rasterizerDiscardEnable
            vk::PolygonMode::eFill,                       // polygonMode
            vk::CullModeFlagBits::eBack,                  // cullMode
            vk::FrontFace::eClockwise,                    // frontFace
            false,                                        // depthBiasEnable
            0.0f,                                         // depthBiasConstantFactor
            0.0f,                                         // depthBiasClamp
            0.0f,                                         // depthBiasSlopeFactor
            1.0f                                          // lineWidth
    );

    vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(
            vk::PipelineMultisampleStateCreateFlags(),  // flags
            vk::SampleCountFlagBits::e1                 // rasterizationSamples
            // other values can be default
    );

    vk::StencilOpState stencilOpState(
            vk::StencilOp::eKeep, vk::StencilOp::eKeep, vk::StencilOp::eKeep, vk::CompareOp::eAlways);
    vk::PipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
            vk::PipelineDepthStencilStateCreateFlags(),  // flags
            true,                                        // depthTestEnable
            true,                                        // depthWriteEnable
            vk::CompareOp::eLessOrEqual,                 // depthCompareOp
            false,                                       // depthBoundTestEnable
            false,                                       // stencilTestEnable
            stencilOpState,                              // front
            stencilOpState                               // back
    );

    vk::ColorComponentFlags colorComponentFlags(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
                                                vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
    vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(
            false,                   // blendEnable
            vk::BlendFactor::eZero,  // srcColorBlendFactor
            vk::BlendFactor::eZero,  // dstColorBlendFactor
            vk::BlendOp::eAdd,       // colorBlendOp
            vk::BlendFactor::eZero,  // srcAlphaBlendFactor
            vk::BlendFactor::eZero,  // dstAlphaBlendFactor
            vk::BlendOp::eAdd,       // alphaBlendOp
            colorComponentFlags      // colorWriteMask
    );
    vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(
            vk::PipelineColorBlendStateCreateFlags(),  // flags
            false,                                     // logicOpEnable
            vk::LogicOp::eNoOp,                        // logicOp
            pipelineColorBlendAttachmentState,         // attachments
            {{1.0f, 1.0f, 1.0f, 1.0f}}             // blendConstants
    );

    std::array<vk::DynamicState, 2> dynamicStates = {vk::DynamicState::eViewport, vk::DynamicState::eScissor};
    vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(vk::PipelineDynamicStateCreateFlags(),
                                                                      dynamicStates);

    auto pipelineLayout = device->createPipelineLayoutUnique(
            vk::PipelineLayoutCreateInfo(vk::PipelineLayoutCreateFlags()));


    vk::Format colourFormat = swapChainImageFormat;
    vk::Format depthFormat = vk::Format::eD16Unorm;

    std::vector<vk::AttachmentDescription> attachmentDescritptions = {
            vk::AttachmentDescription(vk::AttachmentDescriptionFlags(),
                                      colourFormat,
                                      vk::SampleCountFlagBits::e1,
                                      vk::AttachmentLoadOp::eClear,
                                      vk::AttachmentStoreOp::eStore,
                                      vk::AttachmentLoadOp::eDontCare,
                                      vk::AttachmentStoreOp::eDontCare,
                                      vk::ImageLayout::eUndefined,
                                      vk::ImageLayout::ePresentSrcKHR
            ),
            vk::AttachmentDescription(vk::AttachmentDescriptionFlags(),
                                      depthFormat,
                                      vk::SampleCountFlagBits::e1,
                                      vk::AttachmentLoadOp::eClear,
                                      vk::AttachmentStoreOp::eDontCare,
                                      vk::AttachmentLoadOp::eDontCare,
                                      vk::AttachmentStoreOp::eDontCare,
                                      vk::ImageLayout::eUndefined,
                                      vk::ImageLayout::eDepthStencilAttachmentOptimal
            )
    };

    vk::AttachmentReference colorReference(0, vk::ImageLayout::eColorAttachmentOptimal);
    vk::AttachmentReference depthReference(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);
    vk::SubpassDescription subpass(
            vk::SubpassDescriptionFlags(), vk::PipelineBindPoint::eGraphics, {}, colorReference, {}, &depthReference);

    auto renderPass = device->createRenderPassUnique(
            vk::RenderPassCreateInfo((vk::RenderPassCreateFlags()), attachmentDescritptions, subpass));

    vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo(
            (vk::PipelineCreateFlags()),              // flags
            pipelineShaderStageCreateInfos,         // stages
            &pipelineVertexInputStateCreateInfo,    // pVertexInputState
            &pipelineInputAssemblyStateCreateInfo,  // pInputAssemblyState
            nullptr,                                // pTessellationState
            &pipelineViewportStateCreateInfo,       // pViewportState
            &pipelineRasterizationStateCreateInfo,  // pRasterizationState
            &pipelineMultisampleStateCreateInfo,    // pMultisampleState
            &pipelineDepthStencilStateCreateInfo,   // pDepthStencilState
            &pipelineColorBlendStateCreateInfo,     // pColorBlendState
            &pipelineDynamicStateCreateInfo,        // pDynamicState
            *pipelineLayout,                         // layout
            *renderPass                              // renderPass
    );

    vk::Result result;
    vk::Pipeline pipeline;
    std::tie(result, pipeline) = device->createGraphicsPipeline(nullptr, graphicsPipelineCreateInfo);
    switch (result) {
        case vk::Result::eSuccess:
            break;
        case vk::Result::ePipelineCompileRequiredEXT:
            // something meaningfull here
            break;
        default:
            assert(false);  // should never happen
    }

    std::vector<vk::Framebuffer> framebuffers;
    framebuffers.reserve(swapChainImageViews.size() );
    for ( auto const & imageView : swapChainImageViews)
    {
        auto attachments = imageView;
        vk::FramebufferCreateInfo framebufferCreateInfo(
                vk::FramebufferCreateFlags(), *renderPass, attachments, swapChainExtent.width, swapChainExtent.height, 1 );
        framebuffers.push_back( device->createFramebuffer( framebufferCreateInfo ) );
    }

    // create a CommandPool to allocate a CommandBuffer from
    auto commandPool =
            device->createCommandPoolUnique( vk::CommandPoolCreateInfo( vk::CommandPoolCreateFlags(), indices.graphicsFamily.value() ) );

    // allocate a CommandBuffer from the CommandPool
    vk::CommandBuffer commandBuffer =
            device->allocateCommandBuffers( vk::CommandBufferAllocateInfo( *commandPool, vk::CommandBufferLevel::ePrimary, 1 ) )
                    .front();

    auto             imageAcquiredSemaphore = device->createSemaphoreUnique( vk::SemaphoreCreateInfo() );
    vk::ResultValue<uint32_t> currentBuffer =
            device->acquireNextImageKHR(swapChain, UINT64_MAX /* fence timeout */, *imageAcquiredSemaphore, nullptr );
    assert( currentBuffer.result == vk::Result::eSuccess );
    assert( currentBuffer.value < framebuffers.size() );

    commandBuffer.begin( vk::CommandBufferBeginInfo( vk::CommandBufferUsageFlags() ) );

    while (!glfwWindowShouldClose(hWnd)) { glfwPollEvents(); }

    for ( auto const & framebuffer : framebuffers )
    {
        device->destroyFramebuffer( framebuffer );
    }

    for (auto imageView: swapChainImageViews) {
        device->destroyImageView(imageView);
    }

    // not using UniqueSwapChain to destroy in correct order - before the surface
    device->destroySwapchainKHR(swapChain);
    // surface is created by glfw, therefore not using a Unique handle
    instance->destroySurfaceKHR(surface);

    device->destroyPipeline(pipeline);

    glfwDestroyWindow(hWnd);
    glfwTerminate();

    return 0;
}
