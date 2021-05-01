#include "make_tileset.hpp"

#include "core/algorithms.hpp"

namespace wanderer {
namespace {

void make_tiles(entt::registry& registry,
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
        registry.emplace<comp::tile_animation>(entity, *fancy.animation);
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

auto make_tileset(const std::vector<ir::tileset>& data,
                  entt::registry& registry,
                  const graphics_context& graphics) -> ctx::tileset&
{
  auto& tileset = registry.set<ctx::tileset>();

  tileset.tiles.reserve(accumulate(data, [](const ir::tileset& tileset) {
    return tileset.tiles.size();
  }));

  for (const auto& ts : data)
  {
    make_tiles(registry, tileset, ts.tiles, graphics);
  }

  return tileset;
}

}  // namespace wanderer
