#include "saves_menu_entry_factory_system.hpp"

#include <utility>  // move

#include <centurion.hpp>  // surface

namespace wanderer::sys {

auto MakeSavesMenuEntry(entt::registry& registry, const std::filesystem::path& dir)
    -> entt::entity
{
  const auto entity = registry.create();

  auto name = dir.filename().string();
  const auto snapshot = dir / "snapshot.png";
  registry.emplace<comp::SavesMenuEntry>(entity,
                                         std::move(name),
                                         cen::surface{snapshot.string()});

  return entity;
}

}  // namespace wanderer::sys
