#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "display/window.h"
#include "display/window_stats.h"
#include "pbr_api.h"

#include <vulkan/vulkan.h>

#include <vector>

namespace pbr {

class PBR_API App {
 public:
  App();
  App(int window_width, int window_height, const char* window_title);

  void Init();
  void MainLoop();

  virtual void OnInit() {};
  virtual void OnUpdate() {};
  virtual void OnRender() {};
  virtual void OnShutdown() {};

  WindowStats GetWindowStats();

  void Shutdown();

  ~App();

 private:
  void SetLayersFlag();
  bool CheckValidationLayers();
  void CreateAppInfo();
  void CreateInstanceCreationInfo();
  void CreateInstance();

 private:
  Window window_;
  VkInstance instance_;
  VkApplicationInfo app_info_;
  VkInstanceCreateInfo create_info_;

  bool enable_validation_layers_;

  // TODO: string_view instead of const char*
 private:
  const std::vector<const char*> validation_layers_ = {
      "VK_LAYER_KHRONOS_validation"};
};

}  // namespace pbr

#endif  // SRC_APP_H_
