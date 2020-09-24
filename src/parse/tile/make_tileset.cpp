#include "make_tileset.hpp"

#include <cassert>

#include "component/animated.hpp"
#include "component/tileset.hpp"
#include "image_loader.hpp"
#include "index_to_matrix.hpp"
#include "make_tile.hpp"

namespace wanderer {
namespace {

void create_tiles(entt::registry& registry,
                  comp::tileset& tileset,
                  const step::tileset& stepTileset,
                  const entt::handle<cen::texture>& sheet) noexcept
{
  assert(sheet);

  auto id = static_cast<tile_id>(stepTileset.first_gid().get());
  for (auto index = 0; index < stepTileset.tile_count(); ++index, ++id) {
    const auto [row, col] = index_to_matrix(index, stepTileset.columns());

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
                  image_cache& imageCache) -> comp::tileset::entity
{
  const auto entity = registry.create();

  auto& tileset = registry.emplace<comp::tileset>(entity);

  for (const auto& stepTileset : tilesets) {
    using namespace std::string_literals;
    const auto path = "resource/map/"s.append(stepTileset->image());
    const entt::hashed_string id{path.data()};

    if (!imageCache.contains(id)) {
      imageCache.load<image_loader>(id, renderer, path.c_str());
    }

    create_tiles(registry, tileset, *stepTileset, imageCache.handle(id));

    const auto firstGID = static_cast<tile_id>(stepTileset->first_gid().get());
    for (const auto& stepTile : stepTileset->tiles()) {
      const auto gid = firstGID + static_cast<tile_id>(stepTile.id().get());
      parse_special_tile(registry, tileset.tiles.at(gid), stepTile, firstGID);
    }
  }

  return comp::tileset::entity{entity};
}

}  // namespace wanderer
