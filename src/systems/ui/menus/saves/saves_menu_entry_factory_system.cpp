#include "saves_menu_entry_factory_system.hpp"

#include <centurion.hpp>  // surface
#include <utility>        // move

namespace wanderer::sys {

auto make_saves_menu_entry(entt::registry& registry, const std::filesystem::path& dir)
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
