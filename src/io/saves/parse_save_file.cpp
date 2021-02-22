#include "parse_save_file.hpp"

#include <fstream>   // ifstream
#include <json.hpp>  // json

namespace wanderer {

auto parse_save_file(const std::filesystem::path& path) -> save_file_info
{
  std::ifstream stream{path};

  nlohmann::json json;
  stream >> json;

  save_file_info contents;

  contents.world = map_id{json.at("world").get<int>()};
  contents.current = map_id{json.at("current_level").get<int>()};

  for (const auto& [key, object] : json.at("levels").items()) {
    const auto id = map_id{object.at("id").get<int>()};
    const auto dataFile = object.at("data").get<std::string>();
    contents.paths.try_emplace(id, path.parent_path() / dataFile);
  }

  return contents;
};

}  // namespace wanderer
