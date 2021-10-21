#include "parse_plant.hpp"

#include <cassert>  // assert
#include <string>   // string
#include <vector>   // vector

#include "io/tmx/common.hpp"
#include "io/tmx/csv.hpp"

namespace wanderer::io {
namespace {

[[nodiscard]] auto parse_tiles(const std::string& csv, const int offset)
    -> std::vector<TileID>
{
  const auto tokens = parse_csv(csv);

  std::vector<TileID> tiles;
  tiles.reserve(tokens.size());

  for (const auto& token : tokens) {
    const TileID tile{offset + rune::from_string<TileID::value_type>(token).value()};
    tiles.push_back(tile);
  }

  return tiles;
}

}  // namespace

auto parse_plant(const ir::level& data, const rune::tmx_object& object) -> comp::Plant
{
  assert(rune::tmx::is_float(object.properties, "rate"));
  assert(rune::tmx::is_string(object.properties, "tiles"));
  assert(rune::tmx::is_string(object.properties, "tileset"));

  comp::Plant plant;
  plant.rate = rune::tmx::get_float(object.properties, "rate");

  const auto tileset = rune::tmx::get_string(object.properties, "tileset");
  const auto offset = get_tileset_offset(data, tileset);
  const auto tileSize = get_tileset_tile_size(data, tileset);

  plant.tile_height = tileSize->height;
  plant.tiles = parse_tiles(rune::tmx::get_string(object.properties, "tiles"), offset);

  if (const auto* tallTiles = rune::tmx::get_if_string(object.properties, "tallTiles")) {
    plant.tall = parse_tiles(*tallTiles, offset);
  }

  return plant;
}

}  // namespace wanderer::io
