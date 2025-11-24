#include "vulkan_context.h"

#include <GLFW/glfw3.h>

#include <exceptions/vulkan_exception.h>
#include <utility/logger.h>

namespace pbr {



VulkanContext::VulkanContext() : enable_validation_layers_(true) {
  app_info_ = {};
  create_info_ = {};
  instance_ = NULL;
  enable_validation_layers_ = true;
  debug_messenger_ = {};
  messenger_create_info_ = {};
}



void VulkanContext::Init() {
  CreateAppInfo();
  CreateInstance();
  if (VkResult result = CreateDebugUtilsMessengerEXT(
          instance_, &messenger_create_info_, nullptr, &debug_messenger_);
       result != VK_SUCCESS) {
    throw VulkanException("Failed to setup debug messenger", result);
  }
}


VulkanContext::~VulkanContext() {
  if (enable_validation_layers_) {
    DestroyDebugUtilsMessengerEXT(instance_, debug_messenger_, nullptr);
    Logger::Info("Debug messenger destroyed");
  }
  vkDestroyInstance(instance_, nullptr);
  Logger::Info("Vulkan instance destroyed");
}



VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {
  
  switch (messageSeverity) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
      Logger::Trace(" [VULKAN] {}", pCallbackData->pMessage);
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
      Logger::Info(" [VULKAN] {}", pCallbackData->pMessage);
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
      Logger::Warn(" [VULKAN] {}", pCallbackData->pMessage);
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      Logger::Error(" [VULKAN] {}", pCallbackData->pMessage);
      break;
    default:
      Logger::Debug(" [VULKAN] {}", pCallbackData->pMessage);
  }

  return VK_FALSE;
}



void VulkanContext::SetLayersFlag() {
#if defined(DEBUG)
  enable_validation_layers_ = true;
#elif defined(NDEBUG)
  enable_validation_layers_ = false;
#endif
}



bool VulkanContext::CheckValidationLayers() {
  if (!enable_validation_layers_) { return false; }

  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
  std::vector<VkLayerProperties> available_layers(layer_count);

  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

  for (const char* layer_name : validation_layers_) {
    bool layer_found = false;
    for (const auto& layer_properties : available_layers) {
      if (strcmp(layer_name, layer_properties.layerName) == 0) {
        layer_found = true;
        break;
      }
    }
    if (!layer_found) {
      Logger::Error("Failed to find desired Vulkan validation layer.");
      return false;
    }
  }
  Logger::Info("All desired validation layers found successfully.");
  return true;
}



void VulkanContext::CreateAppInfo() {
  app_info_.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info_.pApplicationName = "pbr-lib";
  app_info_.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
  app_info_.pEngineName = "N/A";
  app_info_.engineVersion = VK_MAKE_VERSION(0, 0, 0);
  app_info_.apiVersion = VK_API_VERSION_1_0;
}



void VulkanContext::CreateInstanceCreationInfo() {
  create_info_.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info_.pApplicationInfo = &app_info_;

  GetRequiredExtensions();
  create_info_.enabledExtensionCount = static_cast<uint32_t>(extensions_.size());
  create_info_.ppEnabledExtensionNames = extensions_.data();
  create_info_.enabledLayerCount = 0;
}



void VulkanContext::CreateInstance() {
  SetLayersFlag();

  if (enable_validation_layers_ && !CheckValidationLayers()) {
    VkResult dummy = VK_ERROR_LAYER_NOT_PRESENT;
    throw VulkanException("Desired validation layers not supported.", dummy);
  }

  CreateInstanceCreationInfo();

  if (VkResult result = vkCreateInstance(&create_info_, nullptr, &instance_);
      result != VK_SUCCESS) {
    throw VulkanException("Failed to create vulkan instance.", result);
  }
}



void VulkanContext::GetRequiredExtensions() {
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  extensions_.assign(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if (enable_validation_layers_) {
    extensions_.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }
}



void VulkanContext::SetupDebugMessenger() {
  if (!enable_validation_layers_) return;
  
  messenger_create_info_.sType =
      VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  
  messenger_create_info_.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

  messenger_create_info_.messageType =
      VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  messenger_create_info_.pfnUserCallback = DebugCallback;
  messenger_create_info_.pUserData = nullptr;
}


VkResult VulkanContext::CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger) {

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}



void VulkanContext::DestroyDebugUtilsMessengerEXT(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator) {

  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) { func(instance, debugMessenger, pAllocator); }
}



}  // namespace pbr
