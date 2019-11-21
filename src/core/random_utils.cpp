#include "random_utils.h"
#include <random>

namespace wanderer::core {

int RandomUtils::GetInt(int min, int max) {
  return (rand() % (max + 1 - min)) + min;
}

bool RandomUtils::GetBool() {
  return GetInt(0, 1);
}

}
