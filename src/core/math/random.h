#pragma once
#include <random>

namespace wanderer {

class Random final {
 public:
  Random() noexcept;

  int get_int(int min, int max);

  bool get_bool();

 private:
  using distribution = std::uniform_int_distribution<int>;
  std::default_random_engine m_engine;
  distribution m_distribution;
};

}  // namespace wanderer
