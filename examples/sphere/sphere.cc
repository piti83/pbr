#include <pbr/pbr.h>

class SphereApp : public pbr::App {
  void OnInit() override {
    // Do something on init
  }

  void OnUpdate() override {
    // Do something on frame update
  }

  void OnRender() override {
    // Do something during rendering
  }

  void OnShutdown() override {
    // Do something on app shutdown
  }
};

int main() {
  pbr::Logger::Init();

  pbr::Logger::Critical("{} {} {}", "this", "is", "critical");

  SphereApp sphere;
  sphere.Init();
  sphere.MainLoop();
}
