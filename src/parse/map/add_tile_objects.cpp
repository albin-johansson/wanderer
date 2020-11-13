#include "add_tile_objects.hpp"

#include <algorithm>  // for_each
#include <utility>    // move

#include "centurion_utils.hpp"
#include "component/depth_drawable.hpp"
#include "component/hitbox.hpp"
#include "component/tile_object.hpp"
#include "game_constants.hpp"
#include "hitbox_system.hpp"
#include "index_to_matrix.hpp"
#include "maybe.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_tile_object(entt::registry& registry,
                                    const comp::tile::entity tileEntity,
                                    const int row,
                                    const int col,
                                    const maybe<depth> depth)
    -> comp::tile_object::entity
{
  const auto entity = registry.create();

  auto& object = registry.emplace<comp::tile_object>(entity);
  object.tileEntity = tileEntity;

  constexpr auto tileSize = g_tileSize<float>;
  const auto x = static_cast<float>(col) * tileSize;
  const auto y = static_cast<float>(row) * tileSize;

  const auto& tile = registry.get<comp::tile>(tileEntity.get());
  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = tile.sheet;
  drawable.src = tile.src;
  drawable.dst = {{x, y}, {tileSize, tileSize}};
  drawable.centerY = y + (drawable.dst.height() / 2.0f);
  drawable.zIndex = depth.value_or(5_depth);

  if (const auto* hb = registry.try_get<comp::hitbox>(tileEntity.get())) {
    comp::hitbox hitbox = *hb;
    sys::hitbox::set_position(hitbox, to_vector(drawable.dst.position()));
    registry.emplace<comp::hitbox>(entity, hitbox);
  }

  return comp::tile_object::entity{entity};
}

}  // namespace


void add_tile_objects(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const comp::tileset& tileset,
                      tile_iterator&& begin,
                      tile_iterator&& end)

{
  int index{0};
  std::for_each(begin, end, [&](const step::global_id gid) {
    if (gid.get() != g_emptyTile) {
      const auto tileId = tileset.tiles.at(gid.get());
      const auto [row, col] = index_to_matrix(index, tilemap.cols);
      const auto tileObject =
          make_tile_object(registry, tileId, row, col, std::nullopt);  // FIXME
      tilemap.tileObjects.emplace(comp::map_position{row, col}, tileObject);
    }
    ++index;
  });

  // TODO load actual game objects (items, NPCs, portals to other levels)
}

}  // namespace wanderer
