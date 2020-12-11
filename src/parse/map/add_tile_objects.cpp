#include "add_tile_objects.hpp"

#include <algorithm>  // for_each
#include <utility>    // move

#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "game_constants.hpp"
#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "index_to_matrix.hpp"
#include "tile_object.hpp"

namespace wanderer {
namespace {

void add_depth_drawable(entt::registry& registry,
                        const entt::entity entity,
                        const comp::tile& tile,
                        const cen::fpoint& dstPos)
{
  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = tile.sheet;
  drawable.src = tile.src;
  drawable.dst = {dstPos, {g_tileSize<float>, g_tileSize<float>}};
  drawable.centerY = dstPos.y() + (drawable.dst.height() / 2.0f);
  drawable.zIndex = tile.zIndex;
}

[[nodiscard]] auto make_tile_object(entt::registry& registry,
                                    const comp::tile::entity tileEntity,
                                    const int row,
                                    const int col) -> comp::tile_object::entity
{
  const auto entity = registry.create();
  registry.emplace<comp::tile_object>(entity, tileEntity);

  const cen::fpoint position{static_cast<float>(col) * g_tileSize<float>,
                             static_cast<float>(row) * g_tileSize<float>};

  add_depth_drawable(registry,
                     entity,
                     registry.get<comp::tile>(tileEntity.get()),
                     position);

  if (const auto* tileHb = registry.try_get<comp::hitbox>(tileEntity.get())) {
    auto hitbox = sys::hitbox::with_position(*tileHb, to_vector(position));
    registry.emplace<comp::hitbox>(entity, std::move(hitbox));
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
      const auto tileEntity = tileset.tiles.at(gid.get());
      const auto [row, col] = index_to_matrix(index, tilemap.cols);
      const auto tileObject = make_tile_object(registry, tileEntity, row, col);
      tilemap.tileObjects.emplace(comp::map_position{row, col}, tileObject);
    }
    ++index;
  });

  // TODO load actual game objects (items, NPCs, portals to other levels)
}

}  // namespace wanderer
