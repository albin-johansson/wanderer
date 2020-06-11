#include "make_tileset.h"

#include "animated.h"
#include "make_tile.h"
#include "tileset.h"

namespace wanderer {
namespace {

void fill_tile_identifiers(std::vector<Tile>& tiles,
                           int start,
                           int end,
                           TileID initialValue)
{
  tiles.reserve(tiles.capacity() + static_cast<std::size_t>(end - start));

  for (auto i = start; i < end; ++i) {
    tiles.at(static_cast<std::size_t>(i)).id = initialValue;
    ++initialValue;
  }
}

}  // namespace

entt::entity make_tileset(entt::registry& registry,
                          const std::vector<step::Tileset>& tilesets)
{
  const auto entity{registry.create()};

  auto& tileset = registry.emplace<Tileset>(entity);

  TileID initialValue = 1;

  for (const auto& stepTileset : tilesets) {
    fill_tile_identifiers(tileset.tiles,
                          stepTileset.first_gid(),
                          stepTileset.tile_count(),
                          initialValue);

    for (const auto& stepTile : stepTileset.tiles()) {
      const auto tile{make_tile(registry, stepTile)};
    }
  }

  tileset.tiles.shrink_to_fit();

  return entity;
}

}  // namespace wanderer
