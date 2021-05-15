#pragma once

#include <filesystem>  // path
#include <vector>      // vector

#include "core/aliases/map_id.hpp"

namespace wanderer {

struct save_file_level_info final
{
  map_id id;
  std::filesystem::path path;
  bool outside_level{};
};

struct save_file_info final
{
  map_id current;
  std::vector<save_file_level_info> levels;
};

}  // namespace wanderer
