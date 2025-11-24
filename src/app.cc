#include "app.h"
#include "display/window.h"
#include "exceptions/vulkan_exception.h"

#include <utility/logger.h>

#include <cstring>
#include <vector>

namespace pbr {

App::App() : window_(800, 600, "PBR") {}


App::App(int window_width, int window_height, const char* window_title)
    : window_(window_width, window_height, window_title) {}


void App::Init() {
  window_.Init();
  vulkan_context_.Init();
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


}  // namespace pbr
