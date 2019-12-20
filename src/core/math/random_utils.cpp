#include "random_utils.h"
#include "time_utils.h"
#include <random>
#include <limits>

namespace albinjohansson::wanderer {

uint64_t RandomUtils::GetRand() {
  std::ranlux24_base rnd(TimeUtils::GetHighResTime());
  return static_cast<uint64_t>((rnd() % std::numeric_limits<uint64_t>::max()));
}

int RandomUtils::GetInt(int min, int max) {
  std::ranlux24_base rnd(TimeUtils::GetHighResTime());
  return static_cast<int>((rnd() % (max + 1 - min)) + min);
}

bool RandomUtils::GetBool() {
  return GetInt(0, 99) < 50;
}

}
