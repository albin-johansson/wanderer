#include "random_utils.h"

#include <timer.h>

#include <random>

using namespace centurion;

namespace albinjohansson::wanderer {

int RandomUtils::get_int(int min, int max) noexcept
{
  using distribution = std::uniform_int_distribution<int>;

  static std::default_random_engine engine{
      static_cast<unsigned>(Timer::high_res())};
  static distribution dist{};

  return dist(engine, distribution::param_type{min, max});
}

bool RandomUtils::get_bool()
{
  return get_int(0, 99) < 50;
}

}  // namespace albinjohansson::wanderer
