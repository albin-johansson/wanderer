#include "random_utils.h"
#include <SDL_timer.h>
#include <random>

namespace albinjohansson::wanderer {

int RandomUtils::GetInt(int min, int max) {
  std::ranlux24_base rnd(SDL_GetPerformanceCounter());
  return static_cast<int>((rnd() % (max + 1 - min)) + min);
}

bool RandomUtils::GetBool() {
  return GetInt(0, 99) < 50;
}

}
