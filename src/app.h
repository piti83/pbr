#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "pbr_api.h"
#include "window.h"

#include <vulkan/vulkan.h>

namespace pbr {

class PBR_API App {
 public:
  App();

  void Init();
  void MainLoop();

  virtual void OnInit() {};
  virtual void OnUpdate() {};
  virtual void OnRender() {};
  virtual void OnShutdown() {};

  void Shutdown();

  ~App();

 private:
  void CreateInstance();
 private:
  Window window_;
};

}  // namespace pbr

#endif  // SRC_APP_H_
