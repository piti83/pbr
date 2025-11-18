#include "window.h"
#include "exceptions/window_exception.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace pbr {

Window::Window(int width, int height, const char* title) {
  if (width <= 0) {
    std::cout << "Invalid window width. Creating with default value (800)"
              << std::endl;
    width_ = 800;
  } else {
    width_ = width;
  }

  if (height <= 0) {
    std::cout << "Invalid window height. Creating with default value (600)"
              << std::endl;
    height_ = 600;
  } else {
    height_ = height;
  }

  title_ = title;
}

void Window::Init() {
  if (glfwInit() != GLFW_TRUE) {
    throw pbr::WindowException("Failed to initialise GLFW!");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
  if (window_ == NULL) {
    throw pbr::WindowException("Failed to create glfw window!");
  }
}

GLFWwindow* Window::GetWindow() { return window_; }

int Window::GetWidth() { return width_; }

int Window::GetHeight() { return height_; }

const char* Window::GetTitle() { return title_; }

Window::~Window() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

}  // namespace pbr
