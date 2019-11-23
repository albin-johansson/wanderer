#include "random_utils.h"
#include <random>

namespace albinjohansson::wanderer {

int RandomUtils::GetInt(int min, int max) {
  return (rand() % (max + 1 - min)) + min;
}

bool RandomUtils::GetBool() {
  return GetInt(0, 100) < 50;
}

}
