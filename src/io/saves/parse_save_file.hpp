#pragma once

#include <filesystem>  // path
#include <vector>      // vector

#include "common/map_id.hpp"

namespace wanderer {

struct save_file_level_info final
{
  map_id id;
  std::filesystem::path path;
  bool outside_level{};
  bool keep_viewport_in_bounds{};
};

struct save_file_info final
{
  map_id current;
  std::vector<save_file_level_info> levels;
};

[[nodiscard]] auto parse_save_file(const std::filesystem::path& path) -> save_file_info;

}  // namespace wanderer
