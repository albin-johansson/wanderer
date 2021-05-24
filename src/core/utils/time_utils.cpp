#include "time_utils.hpp"

#include <array>     // array
#include <chrono>    // system_clock
#include <ctime>     // ctime_s
#include <optional>  // optional

using std::chrono::system_clock;

namespace wanderer {

// TODO when MSVC implements the date and time zone additions to std::chrono, use those
//   instead of the old C-style APIs
namespace {

[[nodiscard]] auto stringify(const system_clock::time_point timePoint)
    -> std::optional<std::string>
{
  const auto time = system_clock::to_time_t(timePoint);

  /* Note, ctime is specified to return a string using a format using a total of 24
     characters. However, the MSVC documentation states that the buffer of ctime_s *must*
     be large enough to hold at least 26 characters. */
  std::array<char, 26> buffer;
  if (ctime_s(buffer.data(), buffer.size(), &time) == 0)
  {
    return std::string{buffer.data(), 24};
  }
  else
  {
    return std::nullopt;
  }
}

}  // namespace

[[nodiscard]] auto to_string(const system_clock::time_point timePoint) -> std::string
{
  if (const auto str = stringify(timePoint))
  {
    return *str;
  }
  else
  {
    return "N/A";
  }
}

auto current_hhmmss() -> std::string
{
  const auto str = stringify(system_clock::now()).value();
  return str.substr(11, 8);
}

}  // namespace wanderer
