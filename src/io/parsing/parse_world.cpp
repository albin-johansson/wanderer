#include "parse_world.hpp"

#include <cassert>        // assert
#include <centurion.hpp>  // CENTURION_LOG_INFO
#include <rune.hpp>       // tmx_map, ...

#include "core/game_constants.hpp"
#include "io/parsing/parse_layers.hpp"
#include "io/parsing/parse_tilesets.hpp"

namespace wanderer::io {
namespace {

[[nodiscard]] auto parse_map(const rune::tmx_map& map,
                             const std::filesystem::path& directory) -> ir::level
{
  ir::level data;

  data.col_count = map.width;
  data.row_count = map.height;
  data.tile_width = map.tile_width;
  data.tile_height = map.tile_height;
  data.x_ratio = glob::tile_width<float> / static_cast<float>(data.tile_width);
  data.y_ratio = glob::tile_height<float> / static_cast<float>(data.tile_height);
  data.size.width = static_cast<float>(data.col_count) * glob::tile_width<float>;
  data.size.height = static_cast<float>(data.row_count) * glob::tile_height<float>;

  data.tilesets = parse_tilesets(map.tilesets, directory);

  assert(rune::tmx::is_int(map.properties, "id"));
  assert(rune::tmx::is_int(map.properties, "humanoidLayer"));

  data.id = rune::tmx::get_int(map.properties, "id");
  data.humanoid_layer = rune::tmx::get_int(map.properties, "humanoidLayer");

  parse_layers(map, data);

  return data;
}

}  // namespace

auto parse_world(const std::filesystem::path& world) -> ir::world
{
  CENTURION_LOG_INFO("Parsing main level: %s", world.string().c_str());
  const auto tmx = rune::parse_tmx(world);
  const auto directory = std::filesystem::relative(world).parent_path();

  ir::world data;
  data.base = parse_map(tmx, directory);

  for (const auto& object : data.base.objects)
  {
    if (object.portal)
    {
      const auto levelPath = directory / object.portal->path;
      CENTURION_LOG_INFO("Parsing level: %s", levelPath.string().c_str());

      const auto level = rune::parse_tmx(levelPath);
      data.levels.push_back(parse_map(level, levelPath.parent_path()));
    }
  }

  return data;
}

}  // namespace wanderer::io
