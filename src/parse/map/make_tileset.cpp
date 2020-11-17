#include "make_tileset.hpp"

#include <cassert>  // assert

#include "component/animated.hpp"
#include "component/tileset.hpp"
#include "index_to_matrix.hpp"
#include "make_tile.hpp"
#include "texture_handle.hpp"
#include "texture_loader.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto load_image(std::string_view path,
                              texture_cache& cache,
                              cen::renderer& renderer) -> texture_handle
{
  using namespace std::string_literals;

  const auto result = "resource/map/"s.append(path);
  const entt::hashed_string id{result.c_str()};

  auto handle = cache.load<texture_loader>(id, renderer, result.c_str());
  assert(handle);

  return handle;
}

void create_tiles(entt::registry& registry,
                  comp::tileset& tileset,
                  const step::tileset& stepTileset,
                  const texture_handle& sheet) noexcept
{
  assert(sheet);

  const auto tileWidth = stepTileset.tile_width();
  const auto tileHeight = stepTileset.tile_height();
  const auto tileCount = stepTileset.tile_count();

  auto id = static_cast<tile_id>(stepTileset.first_gid().get());
  for (auto index = 0; index < tileCount; ++index, ++id) {
    const auto [row, col] = index_to_matrix(index, stepTileset.columns());

    const cen::irect src{{col * tileWidth, row * tileHeight},
                         {tileWidth, tileHeight}};

    const auto tileEntity = make_basic_tile(registry, id, sheet, src);

    tileset.tiles.emplace(id, tileEntity);
  }
}

}  // namespace

auto make_tileset(entt::registry& registry,
                  const std::vector<std::unique_ptr<step::tileset>>& tilesets,
                  cen::renderer& renderer,
                  texture_cache& imageCache) -> comp::tileset::entity
{
  const auto entity = registry.create();

  auto& tileset = registry.emplace<comp::tileset>(entity);

  for (const auto& stepTileset : tilesets) {
    const auto handle = load_image(stepTileset->image(), imageCache, renderer);
    create_tiles(registry, tileset, *stepTileset, handle);

    const auto firstGid = static_cast<tile_id>(stepTileset->first_gid().get());
    for (const auto& stepTile : stepTileset->tiles()) {
      const auto gid = firstGid + static_cast<tile_id>(stepTile.id().get());
      parse_fancy_tile(registry, tileset.tiles.at(gid), stepTile, firstGid);
    }
  }

  return comp::tileset::entity{entity};
}

}  // namespace wanderer
