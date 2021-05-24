#include "file_utils.hpp"

#include <chrono>  // time_point_cast, system_clock

#include "time_utils.hpp"

using std::chrono::system_clock;
using std::chrono::time_point_cast;

using file_clock = std::filesystem::file_time_type::clock;

namespace wanderer {

auto last_modified(const std::filesystem::path& path) -> std::string
{
  const auto writeTime = std::filesystem::last_write_time(path);

  const auto timePoint = time_point_cast<system_clock::duration>(
      system_clock::now() + (writeTime - file_clock::now()));

  return to_string(timePoint);
}

}  // namespace wanderer
