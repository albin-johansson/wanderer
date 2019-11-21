#include "random_utils.h"
#include <random>

namespace wanderer::core {

int RandomUtils::GetRand(int min, int max) {
  return (rand() % (max + 1 - min)) + min;
}

bool RandomUtils::GetBool() {
  return GetRand(0, 1);
}

}
