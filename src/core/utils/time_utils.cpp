#include "time_utils.hpp"

#include <ctime>  // ctime_s

using namespace std::chrono;

using file_clock = std::filesystem::file_time_type::clock;

namespace wanderer {

// TODO when MSVC implements the date and time zone additions to std::chrono, use those
//   instead of the old C-style APIs

auto file_modification_time(const std::filesystem::path& path) -> std::string
{
  const auto writeTime = std::filesystem::last_write_time(path);

  const auto timePoint = time_point_cast<system_clock::duration>(
      system_clock::now() + (writeTime - file_clock::now()));

  const auto time = system_clock::to_time_t(timePoint);

  /* Note, ctime is specified to return a string using a format using a total of 24
     characters. However, the MSVC documentation states that the buffer of ctime_s *must*
     be large enough to hold at least 26 characters. */
  char buffer[26];
  if (ctime_s(buffer, sizeof buffer, &time) == 0)
  {
    return std::string{buffer, 24};
  }
  else
  {
    return "N/A";
  }
}

}  // namespace wanderer
