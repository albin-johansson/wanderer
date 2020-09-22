#include "make_tileset.h"

#include <cassert>

#include "animated.h"
#include "image_loader.h"
#include "make_tile.h"
#include "math_utils.h"
#include "tileset.h"

using namespace wanderer::comp;

namespace wanderer {
namespace {

void create_tiles(entt::registry& registry,
                  Tileset& tileset,
                  const step::tileset& stepTileset,
                  const entt::handle<cen::texture>& sheet) noexcept
{
  assert(sheet);

  auto id = static_cast<tile_id>(stepTileset.first_gid().get());
  for (auto index = 0; index < stepTileset.tile_count(); ++index, ++id) {
    const auto [row, col] =
        Math::index_to_matrix_pos(index, stepTileset.columns());

    const auto x = col * stepTileset.tile_width();
    const auto y = row * stepTileset.tile_height();
    const cen::irect src{{x, y},
                         {stepTileset.tile_width(), stepTileset.tile_height()}};

    const auto tileEntity = make_basic_tile(registry, id, sheet, src);

    tileset.tiles.emplace(id, tileEntity);
  }
}

}  // namespace

auto make_tileset(entt::registry& registry,
                  const std::vector<std::unique_ptr<step::tileset>>& tilesets,
                  cen::renderer& renderer,
                  image_cache& imageCache) -> Tileset::entity
{
  const auto entity = registry.create();

  auto& tileset = registry.emplace<Tileset>(entity);

  for (const auto& stepTileset : tilesets) {
    using namespace std::string_literals;
    const auto path = "resource/map/"s.append(stepTileset->image());
    const entt::hashed_string id{path.data()};

    if (!imageCache.contains(id)) {
      imageCache.load<ImageLoader>(id, renderer, path.c_str());
    }

    create_tiles(registry, tileset, *stepTileset, imageCache.handle(id));

    const auto firstGID = static_cast<tile_id>(stepTileset->first_gid().get());
    for (const auto& stepTile : stepTileset->tiles()) {
      const auto gid = firstGID + static_cast<tile_id>(stepTile.id().get());
      parse_special_tile(registry, tileset.tiles.at(gid), stepTile, firstGID);
    }
  }

  return Tileset::entity{entity};
}

}  // namespace wanderer
