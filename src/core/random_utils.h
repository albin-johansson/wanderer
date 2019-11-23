#pragma once

namespace albinjohansson::wanderer {

class RandomUtils final {
 public:
  RandomUtils() = delete;

  ~RandomUtils() = default;

  [[nodiscard]] static int GetInt(int min, int max);

  [[nodiscard]] static bool GetBool();
};

}
