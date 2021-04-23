#include "saves_menu_entry_factory_system.hpp"

#include <centurion.hpp>  // surface
#include <fstream>        // ifstream
#include <json.hpp>       // json

namespace wanderer::sys {

auto make_saves_menu_entry(entt::registry& registry, const std::filesystem::path& dir)
    -> comp::saves_menu_entry::entity
{
  const auto entity = comp::saves_menu_entry::entity{registry.create()};

  const auto saveName = dir.filename().string();
  const auto snapshotPath = dir / "snapshot.png";

  std::ifstream stream{dir / (saveName + ".json")};
  nlohmann::json json;
  stream >> json;

  const auto dataVersion = json.at("data_format_version").get<int>();

  registry.emplace<comp::saves_menu_entry>(entity,
                                           saveName,
                                           cen::surface{snapshotPath.string()},
                                           dataVersion);

  return entity;
}

}  // namespace wanderer::sys
