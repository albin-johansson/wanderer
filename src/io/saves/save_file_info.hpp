#pragma once

#include <filesystem>  // path
#include <map>         // map

#include "core/aliases/map_id.hpp"

namespace wanderer {

struct save_file_info final
{
  map_id world{};
  map_id current{};
  std::map<map_id, std::filesystem::path> paths;
};

}  // namespace wanderer
