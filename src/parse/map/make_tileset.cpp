#include "make_tileset.hpp"

#include <cassert>  // assert

#include "index_to_matrix.hpp"
#include "make_tile.hpp"
#include "texture_handle.hpp"
#include "texture_loader.hpp"
#include "tileset.hpp"

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

[[nodiscard]] auto get_source_rect(const int index,
                                   const int nColumns,
                                   const int tileWidth,
                                   const int tileHeight) noexcept -> cen::irect
{
  const auto [row, col] = index_to_matrix(index, nColumns);

  const cen::irect src{{col * tileWidth, row * tileHeight},
                       {tileWidth, tileHeight}};

  return src;
}

void create_tiles(entt::registry& registry,
                  comp::tileset& tileset,
                  const step::tileset& stepTileset,
                  const texture_handle& sheet) noexcept
{
  assert(sheet);

  const auto tileCount = stepTileset.tile_count();
  const auto tileWidth = stepTileset.tile_width();
  const auto tileHeight = stepTileset.tile_height();

  auto id = static_cast<tile_id>(stepTileset.first_gid().get());
  for (auto index = 0; index < tileCount; ++index, ++id) {
    const auto src =
        get_source_rect(index, stepTileset.columns(), tileWidth, tileHeight);
    tileset.tiles.emplace(id, make_basic_tile(registry, id, sheet, src));
  }
}

void parse_fancy_tiles(entt::registry& registry,
                       comp::tileset& tileset,
                       const step::tileset& stepTileset)
{
  const auto first = static_cast<tile_id>(stepTileset.first_gid().get());
  for (const auto& stepTile : stepTileset.tiles()) {
    const auto gid = first + static_cast<tile_id>(stepTile.id().get());
    parse_fancy_tile(registry, tileset.tiles.at(gid), stepTile, first);
  }
}

}  // namespace

auto make_tileset(entt::registry& registry,
                  const tileset_collection& tilesets,
                  cen::renderer& renderer,
                  texture_cache& imageCache) -> comp::tileset::entity
{
  const comp::tileset::entity entity{registry.create()};

  auto& tileset = registry.emplace<comp::tileset>(entity);
  for (const auto& stepTileset : tilesets) {
    create_tiles(registry,
                 tileset,
                 *stepTileset,
                 load_image(stepTileset->image(), imageCache, renderer));
    parse_fancy_tiles(registry, tileset, *stepTileset);
  }

  return entity;
}

}  // namespace wanderer
