#include "engine.h"

#include <iostream>

namespace pbr {
  void TestFunc(int test_int) {
    std::cout << "Testing function." << std::endl;
    std::cout << "Passed int: " << test_int << std::endl;
  }
}
