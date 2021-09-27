#include "parse_save_file.hpp"

#include <fstream>   // ifstream
#include <json.hpp>  // json
#include <string>    // string

#include "core/aliases/str.hpp"

namespace wanderer {
namespace {

template <typename T>
[[nodiscard]] auto get(const nlohmann::json& json, const str key) -> T
{
  return T{json.at(key).get<typename T::value_type>()};
}

}  // namespace

auto parse_save_file(const std::filesystem::path& path) -> save_file_info
{
  std::ifstream stream{path};

  nlohmann::json json;
  stream >> json;

  save_file_info contents;
  contents.current = get<map_id>(json, "current_level");

  for (const auto& [key, object] : json.at("levels").items()) {
    auto& level = contents.levels.emplace_back();
    level.id = get<map_id>(object, "id");
    level.path = path.parent_path() / object.at("data").get<std::string>();
    object.at("outside_level").get_to(level.outside_level);
    object.at("keep_viewport_in_bounds").get_to(level.keep_viewport_in_bounds);
  }

  return contents;
};

}  // namespace wanderer
