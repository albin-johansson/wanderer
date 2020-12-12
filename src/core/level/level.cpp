#include "level.hpp"

#include <utility>  // move

#include "get_render_bounds.hpp"

namespace wanderer {

level::level(entt::registry&& registry) : m_registry{std::move(registry)}
{}

auto level::make(entt::registry&& registry) -> std::unique_ptr<level>
{
  return std::unique_ptr<level>(new level{std::move(registry)});
}

void level::relocate_aabb(const entt::entity entity, const vector2f& position)
{
  m_aabbTree.relocate(entity, position);
}

auto level::id() const noexcept -> map_id
{
  return m_registry.get<comp::tilemap>(m_tilemap).id;
}

auto level::get_aabb(const entt::entity id) const -> const level::aabb_type&
{
  return m_aabbTree.get_aabb(id);
}

auto level::player() const -> comp::player::entity
{
  return m_player;
}

auto level::viewport() const -> comp::viewport::entity
{
  return m_viewport;
}

auto level::tilemap() const -> comp::tilemap::entity
{
  return m_tilemap;
}

auto level::player_spawnpoint() const -> const vector2f&
{
  return m_playerSpawnPosition.value();
}

auto level::viewport_component() -> comp::viewport&
{
  return m_registry.get<comp::viewport>(m_viewport);
}

auto level::tileset_comp() const -> const comp::tileset&
{
  return m_registry.get<comp::tileset>(m_tileset);
}

auto level::row_count() const -> int
{
  return m_registry.get<comp::tilemap>(m_tilemap).rows;
}

auto level::col_count() const -> int
{
  return m_registry.get<comp::tilemap>(m_tilemap).cols;
}

auto level::get_render_bounds() const -> comp::render_bounds
{
  return sys::get_render_bounds(m_registry,
                                m_viewport,
                                row_count(),
                                col_count());
}

auto level::registry() -> entt::registry&
{
  return m_registry;
}

}  // namespace wanderer
