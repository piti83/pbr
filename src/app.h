#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "pbr_api.h"
#include "display/window.h"
#include "display/window_stats.h"

#include <vulkan/vulkan.h>

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
  void CreateAppInfo();
  void CreateInstanceCreationInfo();
  void CreateInstance();

 private:
  Window window_;
  VkInstance instance_;
  VkApplicationInfo app_info_;
  VkInstanceCreateInfo create_info_;
};

}  // namespace pbr

#endif  // SRC_APP_H_
