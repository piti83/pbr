#ifndef SRC_DISPLAY_WINDOWSTATS_H_
#define SRC_DISPLAY_WINDOWSTATS_H_

#include "pbr_api.h"

namespace pbr {

struct PBR_API WindowStats {
  int width, height;
  int pos_x, pos_y;
  const char* title;
};

}  // namespace pbr

#endif  // SRC_DISPLAY_WINDOWSTATS_H_