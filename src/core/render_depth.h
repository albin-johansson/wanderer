#pragma once

namespace albinjohansson::wanderer {

struct RenderDepth final {
  static constexpr int MIN = 0;
  static constexpr int MAX = 9;
  static constexpr int RANGE = MAX + 1;

  RenderDepth() = delete;

  ~RenderDepth() = default;
};

}
