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

 private:
  void SetLayersFlag();
  bool CheckValidationLayers();
  void CreateAppInfo();
  void CreateInstanceCreationInfo();
  void CreateInstance();

 private:
  VkInstance instance_;
  VkApplicationInfo app_info_;
  VkInstanceCreateInfo create_info_;

  const std::vector<const char*> validation_layers_ = {
      "VK_LAYER_KHRONOS_validation"};

  bool enable_validation_layers_;
};

}  // namespace pbr

#endif  // SRC_CORE_VULKANCONTEXT_H_