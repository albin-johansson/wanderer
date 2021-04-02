#include "create_tileset.hpp"

#include <cstddef>  // size_t

namespace wanderer {
namespace {

void create_tiles(entt::registry& registry,
                  ctx::tileset& tileset,
                  const std::map<tile_id, ir::tile>& tiles,
                  const graphics_context& graphics)
{
  for (const auto& [id, tileData] : tiles)
  {
    const auto entity = comp::tile::entity{registry.create()};
    tileset.tiles.try_emplace(id, entity);

    auto& tile = registry.emplace<comp::tile>(entity);
    tile.id = id;
    tile.texture = graphics.to_index(tileData.texture);
    tile.src = tileData.source;

    if (tileData.fancy)
    {
      const auto& fancy = *tileData.fancy;
      tile.depth = fancy.depth;

      if (fancy.animation)
      {
        registry.emplace<comp::animated_tile>(entity, *fancy.animation);
      }
    }
  }
}

}  // namespace

void load_tileset_textures(const ir::level& data, graphics_context& graphics)
{
  for (const auto& ts : data.tilesets)
  {
    graphics.load(ts.sheet.id, ts.sheet.path);
  }
}

auto create_tileset(const std::vector<ir::tileset>& data,
                    entt::registry& registry,
                    const graphics_context& graphics) -> ctx::tileset&
{
  auto& tileset = registry.set<ctx::tileset>();

  std::size_t nTiles{};
  for (const auto& ts : data)
  {
    for (const auto& tile : ts.tiles)
    {
      ++nTiles;
    }
  }

  tileset.tiles.reserve(nTiles);

  for (const auto& ts : data)
  {
    create_tiles(registry, tileset, ts.tiles, graphics);
  }

  return tileset;
}

}  // namespace wanderer
