#include "time_utils.hpp"

#include <chrono>  // system_clock, zoned_time, current_zone
#include <format>  // format

using std::chrono::current_zone;
using std::chrono::system_clock;
using std::chrono::zoned_time;

namespace wanderer {

auto ConvertToString(const system_clock::time_point tp) -> std::string
{
  const zoned_time zoned{current_zone(), tp};
  return std::format("{:%F %H:%M:%OS}", zoned);
}

auto GetCurrentHHMMSS() -> std::string
{
  const zoned_time time{current_zone(), system_clock::now()};
  return std::format("{:%T}", time);
}

}  // namespace wanderer
