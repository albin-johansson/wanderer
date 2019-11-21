#pragma once

namespace wanderer::core {

class RandomUtils final {
 public:
  RandomUtils() = delete;

  ~RandomUtils() = default;

  [[nodiscard]] static int GetRand(int min, int max);

  [[nodiscard]] static bool GetBool();
};

}
