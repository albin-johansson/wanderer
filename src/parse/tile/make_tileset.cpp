#include "make_tileset.h"

#include <cassert>

#include "animated.h"
#include "image_loader.h"
#include "make_tile.h"
#include "math_utils.h"
#include "tileset.h"

using namespace wanderer::component;

namespace wanderer {
namespace {

void create_tiles(entt::registry& registry,
                  Tileset& tileset,
                  const step::Tileset& stepTileset,
                  const entt::handle<ctn::Texture>& sheet) noexcept
{
  assert(sheet);

  auto id = static_cast<TileID>(stepTileset.first_gid());
  for (auto index = 0; index < stepTileset.tile_count(); ++index, ++id) {
    const auto [row, col] =
        Math::index_to_matrix_pos(index, stepTileset.columns());

    const auto x = col * stepTileset.tile_width();
    const auto y = row * stepTileset.tile_height();
    const ctn::IRect src{{x, y},
                         {stepTileset.tile_width(), stepTileset.tile_height()}};

    const auto tileEntity = make_basic_tile(registry, id, sheet, src);

    tileset.tiles.emplace(id, tileEntity);
  }
}

}  // namespace

auto make_tileset(entt::registry& registry,
                  const std::vector<step::Tileset>& tilesets,
                  ctn::Renderer& renderer,
                  ImageCache& imageCache) -> Tileset::entity
{
  const auto entity = registry.create();

  auto& tileset = registry.emplace<Tileset>(entity);

  for (const auto& stepTileset : tilesets) {
    const auto path = "resource/map/" + stepTileset.image();
    const entt::hashed_string id{path.data()};

    if (!imageCache.contains(id)) {
      imageCache.load<ImageLoader>(id, renderer, path.c_str());
    }

    create_tiles(registry, tileset, stepTileset, imageCache.handle(id));

    const auto firstGID = static_cast<TileID>(stepTileset.first_gid());
    for (const auto& stepTile : stepTileset.tiles()) {
      const auto gid = firstGID + static_cast<TileID>(stepTile.id());
      parse_special_tile(registry, tileset.tiles.at(gid), stepTile, firstGID);
    }
  }

  return Tileset::entity{entity};
}

}  // namespace wanderer
