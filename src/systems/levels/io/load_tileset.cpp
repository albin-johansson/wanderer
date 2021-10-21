#include "load_tileset.hpp"

#include "core/algorithms/accumulate.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

void MakeFancy(entt::registry& registry,
               const entt::entity tileEntity,
               comp::Tile& tile,
               const ir::fancy_tile& data)
{
  tile.depth = data.depth;

  if (data.animation) {
    registry.emplace<comp::TileAnimation>(tileEntity, *data.animation);
  }
}

[[nodiscard]] auto CreateTile(entt::registry& registry,
                              const GraphicsContext& graphics,
                              const TileID id,
                              const ir::tile& data) -> entt::entity
{
  const auto entity = registry.create();

  auto& tile = registry.emplace<comp::Tile>(entity);
  tile.id = id;
  tile.texture = graphics.to_index(data.texture);
  tile.src = data.source;

  if (data.fancy) {
    MakeFancy(registry, entity, tile, *data.fancy);
  }

  return entity;
}

void LoadTiles(entt::registry& registry,
               comp::Tileset& tileset,
               const GraphicsContext& graphics,
               const std::map<TileID, ir::tile>& tiles)
{
  for (const auto& [id, data] : tiles) {
    const auto entity = CreateTile(registry, graphics, id, data);
    tileset.tiles.try_emplace(id, entity);
  }
}

}  // namespace

void LoadTileset(entt::registry& registry,
                 const entt::entity tilesetEntity,
                 const GraphicsContext& graphics,
                 const std::vector<ir::tileset>& data)
{
  auto& tileset = registry.emplace<comp::Tileset>(tilesetEntity);

  tileset.tiles.reserve(
      Accumulate(data, [](const ir::tileset& tileset) { return tileset.tiles.size(); }));

  for (const auto& ts : data) {
    LoadTiles(registry, tileset, graphics, ts.tiles);
  }
}

}  // namespace wanderer::sys
