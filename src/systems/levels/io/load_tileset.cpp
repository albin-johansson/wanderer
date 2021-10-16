#include "load_tileset.hpp"

#include "common/tile_id.hpp"
#include "core/algorithms/accumulate.hpp"

namespace wanderer::sys {
namespace {

void make_fancy(entt::registry& registry,
                const entt::entity tileEntity,
                comp::Tile& tile,
                const ir::fancy_tile& data)
{
  tile.depth = data.depth;

  if (data.animation) {
    registry.emplace<comp::TileAnimation>(tileEntity, *data.animation);
  }
}

[[nodiscard]] auto create_tile(entt::registry& registry,
                               const graphics_context& graphics,
                               const tile_id id,
                               const ir::tile& data) -> entt::entity
{
  const auto entity = registry.create();

  auto& tile = registry.emplace<comp::Tile>(entity);
  tile.id = id;
  tile.texture = graphics.to_index(data.texture);
  tile.src = data.source;

  if (data.fancy) {
    make_fancy(registry, entity, tile, *data.fancy);
  }

  return entity;
}

void load_tiles(entt::registry& registry,
                comp::Tileset& tileset,
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
                  const entt::entity tilesetEntity,
                  const graphics_context& graphics,
                  const std::vector<ir::tileset>& data)
{
  auto& tileset = registry.emplace<comp::Tileset>(tilesetEntity);

  tileset.tiles.reserve(
      accumulate(data, [](const ir::tileset& tileset) { return tileset.tiles.size(); }));

  for (const auto& ts : data) {
    load_tiles(registry, tileset, graphics, ts.tiles);
  }
}

}  // namespace wanderer::sys
