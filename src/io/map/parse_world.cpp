#include "parse_world.hpp"

#include <rune.hpp>

#include "core/game_constants.hpp"
#include "io/map/parse_layers.hpp"
#include "io/map/parse_tilesets.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto parse_map(const rune::tmx_map& map,
                             const std::filesystem::path& directory) -> ir::level
{
  static int tilesetId = 0;

  ir::level data;

  data.nCols = map.width;
  data.nRows = map.height;
  data.tileWidth = map.tile_width;
  data.tileHeight = map.tile_height;
  data.xRatio = glob::tile_width<> / static_cast<float>(data.tileWidth);
  data.yRatio = glob::tile_height<> / static_cast<float>(data.tileHeight);
  data.size.width = static_cast<float>(data.nCols) * glob::tile_width<>;
  data.size.height = static_cast<float>(data.nRows) * glob::tile_height<>;

  data.tilesets = parse_tilesets(map.tilesets, directory);
  ++tilesetId;

  const auto& properties = map.properties;
  assert(rune::tmx::is_int(properties, "id"));
  assert(rune::tmx::is_int(properties, "humanoidLayer"));

  data.id = rune::tmx::get_int(properties, "id");
  data.humanoidLayer = rune::tmx::get_int(properties, "humanoidLayer");

  parse_layers(map, data);

  return data;
}

}  // namespace

auto parse_world(const std::filesystem::path& world) -> ir::world
{
  const auto tmx = rune::parse_tmx(world);
  const auto directory = std::filesystem::relative(world).parent_path();

  ir::world data;
  data.base = parse_map(tmx, directory);

  for (const auto& object : data.base.objects)
  {
    if (object.portal)
    {
      const auto levelPath = directory / object.portal->path;
      const auto level = rune::parse_tmx(levelPath);
      data.levels.push_back(parse_map(level, levelPath.parent_path()));
    }
  }

  return data;
}

}  // namespace wanderer
