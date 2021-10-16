#include "parse_tilesets.hpp"

#include <entt.hpp>  // hashed_string
#include <utility>   // move

#include "core/game_constants.hpp"
#include "io/tmx/tiles/parse_tile.hpp"

namespace wanderer::io {
namespace {

[[nodiscard]] auto make_texture(const std::filesystem::path& path) -> ir::texture
{
  ir::texture texture;

  auto str = path.string();
  texture.id = texture_id{entt::hashed_string{str.c_str()}};
  texture.path = std::move(str);

  return texture;
}

void add_tiles(ir::tileset& data, const rune::tmx_tileset& tileset)
{
  auto id = static_cast<tile_id>(tileset.first_id.get());
  for (auto index = 0; index < tileset.tile_count; ++index, ++id) {
    data.tiles.emplace(id, make_tile(id, index, data.sheet.id, tileset));
  }
}

void add_fancy_tiles(ir::tileset& data, const rune::tmx_tileset& tileset)
{
  const auto first = static_cast<tile_id>(tileset.first_id.get());
  for (const auto& tsTile : tileset.tiles) {
    const auto gid = first + static_cast<tile_id>(tsTile.id.get());
    auto& tile = data.tiles.at(gid);
    tile.fancy = parse_fancy_tile(data, tsTile, first);
  }
}

}  // namespace

auto parse_tilesets(const rune::tmx_tilesets& tilesets,
                    const std::filesystem::path& directory) -> std::vector<ir::tileset>
{
  std::vector<ir::tileset> results;

  for (const auto& tileset : tilesets) {
    auto& data = results.emplace_back();

    data.name = tileset.name;
    data.sheet = make_texture(directory / tileset.image);
    data.x_ratio = glob::tile_width<float> / static_cast<float>(tileset.tile_width);
    data.y_ratio = glob::tile_height<float> / static_cast<float>(tileset.tile_height);
    data.tile_width = tileset.tile_width;
    data.tile_height = tileset.tile_height;

    add_tiles(data, tileset);
    add_fancy_tiles(data, tileset);
  }

  return results;
}

}  // namespace wanderer::io
