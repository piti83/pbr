#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace pbr {

class Window {
 public:
  Window(int width, int height, const char* title);
  GLFWwindow* GetWindow();
  ~Window();

 private:
  GLFWwindow* window_;
};

}  // namespace pbr

#endif
