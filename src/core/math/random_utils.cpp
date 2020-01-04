#include "random_utils.h"
#include "time_utils.h"
#include <random>
#include <limits>

namespace albinjohansson::wanderer {

uint64_t RandomUtils::get_rand() {
  std::ranlux24_base rnd(TimeUtils::get_high_res_time());
  return static_cast<uint64_t>((rnd() % std::numeric_limits<uint64_t>::max()));
}

int RandomUtils::get_int(int min, int max) {
  std::ranlux24_base rnd(TimeUtils::get_high_res_time());
  return static_cast<int>((rnd() % (max + 1 - min)) + min);
}

bool RandomUtils::get_bool() {
  return get_int(0, 99) < 50;
}

}
