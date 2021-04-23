#include "saves_menu_entry_factory_system.hpp"

#include <centurion.hpp>  // surface
#include <fstream>        // ifstream
#include <json.hpp>       // json

namespace wanderer::sys {

auto make_saves_menu_entry(entt::registry& registry, const std::filesystem::path& path)
    -> comp::saves_menu_entry::entity
{
  const auto entity = comp::saves_menu_entry::entity{registry.create()};

  const auto saveName = path.filename().string();
  const auto snapshotPath = path / "snapshot.png";

  std::ifstream stream{path / (saveName + ".json")};
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
