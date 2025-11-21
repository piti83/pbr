#include "app.h"
#include "display/window.h"
#include "exceptions/vulkan_exception.h"

#include <utility/logger.h>

#include <cstring>
#include <vector>

namespace pbr {

App::App() : window_(800, 600, "PBR") {
  app_info_ = {};
  create_info_ = {};
  instance_ = NULL;
  enable_validation_layers_ = true;
}

App::App(int window_width, int window_height, const char* window_title)
    : window_(window_width, window_height, window_title) {
  app_info_ = {};
  create_info_ = {};
  instance_ = NULL;
  enable_validation_layers_ = true;
}

void App::Init() {
  CreateAppInfo();
  CreateInstance();
  window_.Init();
}

void App::MainLoop() {
  while (!glfwWindowShouldClose(window_.GetWindow())) { glfwPollEvents(); }
}

WindowStats App::GetWindowStats() {
  WindowStats stats;

  glfwGetWindowSize(window_.GetWindow(), &stats.width, &stats.height);
  glfwGetWindowPos(window_.GetWindow(), &stats.pos_x, &stats.pos_y);
  stats.title = glfwGetWindowTitle(window_.GetWindow());

  return stats;
}

void App::Shutdown() {}

App::~App() {}

void App::SetLayersFlag() {
#if defined(DEBUG)
  enable_validation_layers_ = true;
#elif defined(NDEBUG)
  enable_validation_layers_ = false;
#endif
}

bool App::CheckValidationLayers() {
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

void App::CreateAppInfo() {
  app_info_.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info_.pApplicationName = "pbr-lib";
  app_info_.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
  app_info_.pEngineName = "N/A";
  app_info_.engineVersion = VK_MAKE_VERSION(0, 0, 0);
  app_info_.apiVersion = VK_API_VERSION_1_0;
}

void App::CreateInstanceCreationInfo() {
  create_info_.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info_.pApplicationInfo = &app_info_;

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  create_info_.enabledExtensionCount = glfwExtensionCount;
  create_info_.ppEnabledExtensionNames = glfwExtensions;
  create_info_.enabledLayerCount = 0;

  if (enable_validation_layers_) {
    create_info_.enabledLayerCount =
        static_cast<uint32_t>(validation_layers_.size());
    create_info_.ppEnabledLayerNames = validation_layers_.data();
  } else {
    create_info_.enabledLayerCount = 0;
  }
}

void App::CreateInstance() {
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

}  // namespace pbr
