#include "add_tile_objects.hpp"

#include <algorithm>  // for_each
#include <utility>    // move

#include "component/depth_drawable.hpp"
#include "game_constants.hpp"
#include "index_to_matrix.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_tile_object(entt::registry& registry,
                                    entt::entity tileID,
                                    int row,
                                    int col) -> entt::entity
{
  const auto entity = registry.create();
  const auto tileSize = g_tileSize<float>;

  const auto x = static_cast<float>(col) * tileSize;
  const auto y = static_cast<float>(row) * tileSize;

  const auto& tile = registry.get<comp::tile>(tileID);

  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = tile.sheet;
  drawable.src = tile.src;
  drawable.dst = {{x, y}, {tileSize, tileSize}};
  drawable.centerY = y + (drawable.dst.height() / 2.0f);
  drawable.depth = depth{5};  // FIXME

  return entity;
}

}  // namespace

void add_tile_objects(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const comp::tileset& tileset,
                      tile_iterator&& begin,
                      tile_iterator&& end)

{
  int index{0};
  std::for_each(begin, end, [&](const auto gid) {
    if (gid.get() != g_emptyTile) {
      const auto tileId = tileset.tiles.at(gid.get()).get();
      const auto [row, col] = index_to_matrix(index, tilemap.cols);
      const auto tileObject = make_tile_object(registry, tileId, row, col);
      tilemap.tileObjects.emplace(comp::map_position{row, col}, tileObject);
    }
    ++index;
  });

  // TODO load actual game objects (items, NPCs, portals to other levels)
}

}  // namespace wanderer
