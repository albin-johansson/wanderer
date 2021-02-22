#include "create_tileset.hpp"

#include <cstddef>  // size_t

namespace wanderer {
namespace {

void create_tiles(entt::registry& registry,
                  comp::tileset& tileset,
                  const std::map<tile_id, ir::tile>& tiles)
{
  for (const auto& [id, tileData] : tiles) {
    const auto entity = comp::tile::entity{registry.create()};
    tileset.tiles.try_emplace(id, entity);

    auto& tile = registry.emplace<comp::tile>(entity);
    tile.id = id;
    tile.texture = tileData.texture;
    tile.src = tileData.source;

    if (tileData.fancy) {
      const auto& fancy = *tileData.fancy;
      tile.depth = fancy.depth;

      if (fancy.animation) {
        registry.emplace<comp::animated_tile>(entity, *fancy.animation);
      }
    }
  }
}

}  // namespace

void load_tileset_textures(const ir::level& data, graphics_context& graphics)
{
  for (const auto& ts : data.tilesets) {
    const auto& textureData = ts.sheet;
    graphics.load_texture(textureData.id, textureData.path.c_str());
  }
}

auto create_tileset(const std::vector<ir::tileset>& data,
                    entt::registry& registry,
                    const comp::tileset::entity entity) -> comp::tileset&
{
  auto& tileset = registry.emplace<comp::tileset>(entity);

  std::size_t nTiles{};
  for (const auto& ts : data) {
    for (const auto& tile : ts.tiles) {
      ++nTiles;
    }
  }

  tileset.tiles.reserve(nTiles);

  for (const auto& ts : data) {
    create_tiles(registry, tileset, ts.tiles);
  }

  return tileset;
}

}  // namespace wanderer
