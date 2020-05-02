#pragma once

#include <vector>

namespace Afk {
  struct HeightMap {
    struct Point {
      int x = {};
      int y = {};
    };

    std::vector<float> heights = {};
    int width                  = {};

    auto at(Point p) const -> float;
    auto operator[](Point p) -> float &;
  };
}
