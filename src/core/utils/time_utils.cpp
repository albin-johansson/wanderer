#include "time_utils.hpp"

#include <chrono>  // system_clock, zoned_time, current_zone
#include <format>  // format

namespace chrono = std::chrono;

namespace wanderer {

[[nodiscard]] auto to_string(const chrono::system_clock::time_point tp) -> std::string
{
  const chrono::zoned_time zoned{chrono::current_zone(), tp};
  return std::format("{:%F %H:%M:%OS}", zoned);
}

auto current_hhmmss() -> std::string
{
  const chrono::zoned_time zoned{chrono::current_zone(), chrono::system_clock::now()};
  return std::format("{:%T}", zoned);
}

}  // namespace wanderer
