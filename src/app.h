#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "display/window.h"
#include "display/window_stats.h"
#include "pbr_api.h"

#include <vulkan/vulkan.h>

#include <vector>

#include <core/vulkan_context.h>
#include <display/window.h>

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
  Window window_;
  VulkanContext vulkan_context_;
};

}  // namespace pbr

#endif  // SRC_APP_H_
