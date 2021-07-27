#include "parse_plant.hpp"

#include <cassert>  // assert

#include "io/parsing/common.hpp"
#include "io/parsing/csv.hpp"

namespace wanderer::io {

auto parse_plant(const ir::level& data, const rune::tmx_object& object) -> comp::plant
{
  assert(rune::tmx::is_float(object.properties, "rate"));
  assert(rune::tmx::is_string(object.properties, "tiles"));
  assert(rune::tmx::is_string(object.properties, "tileset"));

  comp::plant plant;
  plant.rate = rune::tmx::get_float(object.properties, "rate");

  const auto tileset = rune::tmx::get_string(object.properties, "tileset");
  const auto offset = get_tileset_offset(data, tileset);

  // TODO allow multiple tiles per frame, e.g. "1,2:3,4,5:6"
  const auto csv = rune::tmx::get_string(object.properties, "tiles");
  const auto tokens = parse_csv(csv);

  plant.tiles.reserve(tokens.size());
  for (const auto& token : tokens)
  {
    const tile_id tile{offset + rune::from_string<tile_id::value_type>(token).value()};
    plant.tiles.push_back(tile);
  }

  return plant;
}

}  // namespace wanderer::io
