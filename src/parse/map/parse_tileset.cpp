#include "parse_tileset.hpp"

#include <cassert>      // assert
#include <entt.hpp>     // hashed_string
#include <map>          // map
#include <string>       // string_literals
#include <string_view>  // string_view

#include "parse_tile.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto create_texture(const std::string_view path,
                                  graphics_context& graphics) -> texture_handle
{
  using namespace std::string_literals;

  const auto result = "resource/map/"s.append(path);
  const entt::hashed_string id{result.c_str()};

  auto handle = graphics.load_texture(id, result.c_str());
  assert(handle);

  return handle;
}

void add_tiles(const step::tileset& tileset, ir::tileset& data)
{
  auto id = static_cast<tile_id>(tileset.first_gid().get());
  const auto tileCount = tileset.tile_count();

  for (auto index = 0; index < tileCount; ++index, ++id) {
    data.tiles.emplace(id, make_tile(id, index, data.texture, tileset));
  }
}

void parse_fancy_tiles(ir::tileset& data, const step::tileset& stepTileset)
{
  const auto first = static_cast<tile_id>(stepTileset.first_gid().get());
  for (const auto& stepTile : stepTileset.tiles()) {
    const auto gid = first + static_cast<tile_id>(stepTile.id().get());
    auto& tile = data.tiles.at(gid);
    tile.fancy = parse_fancy_tile(data, data.tiles.at(gid), stepTile, first);
  }
}

}  // namespace

auto parse_tileset(const tileset_collection& tilesets,
                   graphics_context& graphics) -> ir::tileset
{
  ir::tileset data;

  for (const auto& stepTileset : tilesets) {
    data.texture = create_texture(stepTileset->image(), graphics);
    add_tiles(*stepTileset, data);
    parse_fancy_tiles(data, *stepTileset);
  }

  return data;
}

}  // namespace wanderer
