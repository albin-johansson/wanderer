#pragma once

#include <filesystem>  // path

#include "map_id.hpp"
#include "save_file_info.hpp"

namespace wanderer {

[[nodiscard]] auto parse_save_file(const std::filesystem::path& path)
    -> save_file_info;

}  // namespace wanderer
