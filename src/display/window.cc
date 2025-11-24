#include <display/window.h>
#include <exceptions/window_exception.h>
#include <utility/logger.h>

#include <iostream>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace pbr {



Window::Window(int width, int height, const char* title) {
  if (width <= 0) {
    Logger::Warn("Invalid window width.Creating with default value(800)");
    width_ = 800;
  } else {
    width_ = width;
  }

  if (height <= 0) {
    Logger::Warn("Invalid window height. Creating with default value (600)");
    height_ = 600;
  } else {
    height_ = height;
  }

  title_ = title;
  window_ = nullptr;

  Logger::Trace("Window object created with parameters:");
  Logger::Trace("Width:   {}", width_);
  Logger::Trace("Height:  {}", height_);
  Logger::Trace("Title:   {}", title_);
}



void Window::Init() {
  if (glfwInit() != GLFW_TRUE) {
    Logger::Error("Failed to initialise GLFW!");
    throw pbr::WindowException("Failed to initialise GLFW!");
  } else {
    Logger::Info("GLFW successfully initialised.");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
  if (window_ == NULL) {
    Logger::Error("Failed to create glfw window!");
    throw pbr::WindowException("Failed to create glfw window!");
  } else {
    Logger::Info("Window successfully initialised.");
  }
}

GLFWwindow* Window::GetWindow() { return window_; }

int Window::GetWidth() { return width_; }

int Window::GetHeight() { return height_; }

const char* Window::GetTitle() { return title_; }

Window::~Window() {
  glfwDestroyWindow(window_);
  Logger::Info("GLFW window destroyed.");
  glfwTerminate();
  Logger::Info("GLFW terminated.");
}

}  // namespace pbr
