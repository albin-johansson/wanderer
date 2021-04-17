#pragma once

#include <filesystem>  // path

#include "core/aliases/map_id.hpp"
#include "io/saves/save_file_info.hpp"

namespace wanderer {

[[nodiscard]] auto parse_save_file(const std::filesystem::path& path) -> save_file_info;

}  // namespace wanderer
