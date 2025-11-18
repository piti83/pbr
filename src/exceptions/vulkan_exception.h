#ifndef SRC_EXCEPTIONS_VULKANEXCEPTION_H_
#define SRC_EXCEPTIONS_VULKANEXCEPTION_H_

#include "pbr_api.h"
#include <exception>

#include <vulkan/vulkan.h>

namespace pbr {

class PBR_API VulkanException : public std::exception {
 public:
  VulkanException(const char* message, VkResult vk_result)
      : message_(message), vk_result_(vk_result) {}

  VkResult Result() { return vk_result_; }
  const char* what() { return message_; }

 private:
  const char* message_;
  VkResult vk_result_;
};

}  // namespace pbr

#endif  // SRC_EXCEPTIONS_VULKANEXCEPTION_H_