#include "random.hpp"

#include <algorithm>   // generate
#include <array>       // array
#include <functional>  // ref
#include <random>      // random_device, seed_seq

namespace wanderer {

auto make_random_engine() -> random_engine
{
  using result_type = std::random_device::result_type;

  constexpr auto n = random_engine::state_size;

  std::random_device device;
  std::array<result_type, (n - 1) / sizeof(result_type) + 1> data{};

  std::generate(data.begin(), data.end(), std::ref(device));
  std::seed_seq seeds(data.begin(), data.end());

  return random_engine(seeds);
}

}  // namespace wanderer