#include "window.h"

#include <iostream>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace pbr {

Window::Window(int width, int height, const char* title)  {
  if (glfwVulkanSupported() != GLFW_TRUE) {
    std::cout << "Vulkan supported!" << std::endl;
  } else {
    std::cout << "Vulkan NOT supported!" << std::endl;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

GLFWwindow* Window::GetWindow() {
  return window_;
}

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

}  // namespace pbr
