#include "random_utils.h"

#include "wanderer_stdinc.h"

namespace wanderer {
namespace {

inline std::mt19937 random{std::random_device{}()};

}

int math::random_int(int min, int max)
{
  std::uniform_int_distribution<int> dist{min, max};
  return dist(random);
}

}  // namespace wanderer