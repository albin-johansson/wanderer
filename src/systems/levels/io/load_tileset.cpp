#include "load_tileset.hpp"

#include "common/tile_id.hpp"
#include "core/algorithms/accumulate.hpp"

namespace wanderer::sys {
namespace {

void make_fancy(entt::registry& registry,
                const comp::tile::entity entity,
                comp::tile& tile,
                const ir::fancy_tile& data)
{
  tile.depth = data.depth;

  if (data.animation) {
    registry.emplace<comp::tile_animation>(entity, *data.animation);
  }
}

[[nodiscard]] auto create_tile(entt::registry& registry,
                               const graphics_context& graphics,
                               const tile_id id,
                               const ir::tile& data) -> comp::tile::entity
{
  const auto entity = comp::tile::entity{registry.create()};

  auto& tile = registry.emplace<comp::tile>(entity);
  tile.id = id;
  tile.texture = graphics.to_index(data.texture);
  tile.src = data.source;

  if (data.fancy) {
    make_fancy(registry, entity, tile, *data.fancy);
  }

  return entity;
}

void load_tiles(entt::registry& registry,
                comp::tileset& tileset,
                const graphics_context& graphics,
                const std::map<tile_id, ir::tile>& tiles)
{
  for (const auto& [id, data] : tiles) {
    const auto entity = create_tile(registry, graphics, id, data);
    tileset.tiles.try_emplace(id, entity);
  }
}

}  // namespace

void load_tileset(entt::registry& registry,
                  const comp::tileset::entity entity,
                  const graphics_context& graphics,
                  const std::vector<ir::tileset>& data)
{
  auto& tileset = registry.emplace<comp::tileset>(entity);

  tileset.tiles.reserve(
      accumulate(data, [](const ir::tileset& tileset) { return tileset.tiles.size(); }));

  for (const auto& ts : data) {
    load_tiles(registry, tileset, graphics, ts.tiles);
  }
}

}  // namespace wanderer::sys
