#include "file_utils.hpp"

#include <chrono>  // time_point_cast, system_clock, file_clock

#include "time_utils.hpp"

using std::chrono::file_clock;
using std::chrono::system_clock;
using std::chrono::time_point_cast;

namespace wanderer {

auto last_modified(const std::filesystem::path& path) -> std::string
{
  const auto writeTime = std::filesystem::last_write_time(path);

  const auto timePoint = time_point_cast<system_clock::duration>(
      system_clock::now() + (writeTime - file_clock::now()));

  return to_string(timePoint);
}

}  // namespace wanderer
