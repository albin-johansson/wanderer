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

  contents.current = map_id{json.at("current_level").get<map_id::value_type>()};

  for (const auto& [key, object] : json.at("levels").items())
  {
    auto& level = contents.levels.emplace_back();
    level.id = map_id{object.at("id").get<map_id::value_type>()};
    level.path = path.parent_path() / object.at("data").get<std::string>();
    level.outside_level = object.at("outside_level").get<bool>();
  }

  return contents;
};

}  // namespace wanderer
