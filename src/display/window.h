#ifndef SRC_DISPLAY_WINDOW_H_
#define SRC_DISPLAY_WINDOW_H_

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "pbr_api.h"

namespace pbr {

class PBR_API Window {
 public:
  Window(int width, int height, const char* title);
  void Init();
  GLFWwindow* GetWindow();
  int GetWidth();
  int GetHeight();
  const char* GetTitle();
  ~Window();

 private:
  int width_, height_;
  const char* title_;
  GLFWwindow* window_;
};

}  // namespace pbr

#endif // SRC_DISPLAY_WINDOW_H_
