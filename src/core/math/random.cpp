#include "random.h"

#include <timer.h>

#include "types.h"

using namespace centurion;

namespace wanderer {

Random::Random() noexcept
{
  m_engine.seed(static_cast<u32>(Timer::high_res()));
}

int Random::get_int(const int min, const int max)
{
  return m_distribution(m_engine, distribution::param_type{min, max});
}

bool Random::get_bool()
{
  return get_int(0, 999) < 500;
}

}  // namespace wanderer