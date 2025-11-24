#ifndef SRC_CORE_VULKANCONTEXT_H_
#define SRC_CORE_VULKANCONTEXT_H_

#include <pbr_api.h>

#include <vulkan/vulkan.h>

#include <vector>

namespace pbr {

class PBR_API VulkanContext {
 public:
  VulkanContext();
  void Init();

  ~VulkanContext();

  static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

 private:
  void SetLayersFlag();
  bool CheckValidationLayers();
  void CreateAppInfo();
  void CreateInstanceCreationInfo();
  void CreateInstance();
  void GetRequiredExtensions();
  void SetupDebugMessenger();

  VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
      const VkAllocationCallbacks* pAllocator,
      VkDebugUtilsMessengerEXT* pDebugMessenger);

  void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

 private:
  VkInstance instance_;
  VkApplicationInfo app_info_;
  VkInstanceCreateInfo create_info_;

  VkDebugUtilsMessengerEXT debug_messenger_;
  VkDebugUtilsMessengerCreateInfoEXT messenger_create_info_;


  std::vector<const char*> validation_layers_;
  std::vector<const char*> extensions_;

  bool enable_validation_layers_;
};

}  // namespace pbr

#endif  // SRC_CORE_VULKANCONTEXT_H_