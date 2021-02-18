#include "save_game.hpp"

#include <fstream>   // ofstream
#include <iomanip>   // setw
#include <json.hpp>  // json
#include <string>    // string, to_string

#include "files_directory.hpp"

using json_type = nlohmann::json;

namespace wanderer {

void save_game(const std::string& name, const level_manager& levels)
{
  static const auto savesDir = files_directory() + "saves/";
  const auto dir = savesDir + name + "/";

  std::filesystem::create_directories(dir);

  json_type json;

  json["name"] = name;
  json["json_format_version"] = 1;
  json["data_format_version"] = 1;
  json["current_level"] = levels.current_id().get();
  json["world"] = levels.world().get();

  for (const auto& [id, level] : levels) {
    const auto levelName = "level_" + std::to_string(id.get()) + ".wanderer";
    level->save(dir + levelName);

    json_type levelObject;

    levelObject["id"] = id.get();
    levelObject["data"] = levelName;

    json["levels"].emplace_back(std::move(levelObject));
  }

  std::ofstream stream{dir + name + ".json"};
  stream << std::setw(2) << json;
}

}  // namespace wanderer
