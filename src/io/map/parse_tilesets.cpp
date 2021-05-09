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

void add_tiles(const rune::tmx_tileset& tileset, ir::tileset& data)
{
  auto id = static_cast<tile_id>(tileset.first_id.get());
  for (auto index = 0; index < tileset.tile_count; ++index, ++id)
  {
    data.tiles.emplace(id, make_tile(id, index, data.sheet.id, tileset));
  }
}

void parse_fancy_tiles(ir::tileset& data, const rune::tmx_tileset& tileset)
{
  const auto first = static_cast<tile_id>(tileset.first_id.get());
  for (const auto& tsTile : tileset.tiles)
  {
    const auto gid = first + static_cast<tile_id>(tsTile.id.get());
    auto& tile = data.tiles.at(gid);
    tile.fancy = parse_fancy_tile(data, tile, tsTile, first);
  }
}

}  // namespace

auto parse_tilesets(const std::vector<rune::tmx_tileset>& tilesets,
                    const std::filesystem::path& directory) -> std::vector<ir::tileset>
{
  std::vector<ir::tileset> results;

  for (const auto& ts : tilesets)
  {
    auto& tileset = results.emplace_back();

    tileset.sheet = make_texture(directory / ts.image);
    tileset.xRatio = glob::tile_width<float> / static_cast<float>(ts.tile_width);
    tileset.yRatio = glob::tile_height<float> / static_cast<float>(ts.tile_height);

    add_tiles(ts, tileset);
    parse_fancy_tiles(tileset, ts);
  }

  return results;
}

}  // namespace wanderer
