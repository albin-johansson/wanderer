#include "parse_tilesets.hpp"

#include <entt.hpp>  // hashed_string
#include <utility>   // move

#include "core/game_constants.hpp"
#include "io/map/parse_tile.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_texture(const std::filesystem::path& path) -> ir::texture
{
  ir::texture texture;

  auto str = path.string();
  texture.id = entt::hashed_string{str.c_str()};
  texture.path = std::move(str);

  return texture;
}

void add_tiles(const step::tileset& tileset, ir::tileset& data)
{
  auto id = static_cast<tile_id>(tileset.first_gid().get());
  const auto tileCount = tileset.tile_count();

  for (auto index = 0; index < tileCount; ++index, ++id)
  {
    data.tiles.emplace(id, make_tile(id, index, data.sheet.id, tileset));
  }
}

void parse_fancy_tiles(ir::tileset& data, const step::tileset& stepTileset)
{
  const auto first = static_cast<tile_id>(stepTileset.first_gid().get());
  for (const auto& stepTile : stepTileset.tiles())
  {
    const auto gid = first + static_cast<tile_id>(stepTile.id().get());
    auto& tile = data.tiles.at(gid);
    tile.fancy = parse_fancy_tile(data, data.tiles.at(gid), stepTile, first);
  }
}

}  // namespace

auto parse_tilesets(const tileset_collection& tilesets,
                    const std::filesystem::path& directory) -> std::vector<ir::tileset>
{
  std::vector<ir::tileset> vec;

  for (const auto& stepTileset : tilesets)
  {
    auto& tileset = vec.emplace_back();

    const auto path = directory / stepTileset->image();
    tileset.sheet = make_texture(path);
    tileset.xRatio = glob::tile_width<> / stepTileset->tile_width();
    tileset.yRatio = glob::tile_height<> / stepTileset->tile_height();

    add_tiles(*stepTileset, tileset);
    parse_fancy_tiles(tileset, *stepTileset);
  }

  return vec;
}

}  // namespace wanderer
