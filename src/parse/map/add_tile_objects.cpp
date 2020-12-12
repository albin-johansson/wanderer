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
                        const cen::fpoint& dstPos,
                        const int layerIndex)
{
  auto& drawable = registry.emplace<comp::depth_drawable>(entity);
  drawable.texture = tile.sheet;
  drawable.src = tile.src;
  drawable.dst = {dstPos, {g_tileSize<float>, g_tileSize<float>}};
  drawable.centerY = dstPos.y() + (drawable.dst.height() / 2.0f);
  drawable.depth = tile.depth;
  drawable.layer = layerIndex;
}


[[nodiscard]] auto make_tile_object(entt::registry& registry,
                                    const comp::tile::entity tileEntity,
                                    const int row,
                                    const int col,
                                    const int layerIndex)
    -> comp::tile_object::entity
{
  const auto entity = registry.create();
  registry.emplace<comp::tile_object>(entity, tileEntity);

  const cen::fpoint position{static_cast<float>(col) * g_tileSize<float>,
                             static_cast<float>(row) * g_tileSize<float>};

  add_depth_drawable(registry,
                     entity,
                     registry.get<comp::tile>(tileEntity),
                     position,
                     layerIndex);

  if (const auto* tileHb = registry.try_get<comp::hitbox>(tileEntity)) {
    auto hitbox = sys::hitbox::with_position(*tileHb, to_vector(position));
    registry.emplace<comp::hitbox>(entity, std::move(hitbox));
  }

  return comp::tile_object::entity{entity};
}

}  // namespace

void add_tile_objects(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const comp::tileset& tileset,
                      const tile_data& data,
                      const int layerIndex)

{
  int index{0};

  for (const auto gid : data) {
    if (gid.get() != g_emptyTile) {
      const auto tileEntity = tileset.tiles.at(gid.get());
      const auto [row, col] = index_to_matrix(index, tilemap.cols);
      const auto tileObject =
          make_tile_object(registry, tileEntity, row, col, layerIndex);
      tilemap.tileObjects.emplace(comp::map_position{row, col}, tileObject);
    }
    ++index;
  }

  // TODO load actual game objects (items, NPCs, portals to other levels)
}

}  // namespace wanderer
