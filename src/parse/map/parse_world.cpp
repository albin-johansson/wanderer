#include "parse_world.hpp"

#include <step_map.hpp>

#include "game_constants.hpp"
#include "parse_layers.hpp"
#include "parse_tileset.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto parse_map(const step::map& stepMap,
                             graphics_context& graphics) -> ir::level
{
  static int tilesetId = 0;

  ir::level data;

  data.nCols = stepMap.width();
  data.nRows = stepMap.height();
  data.size.width = static_cast<float>(data.nCols) * glob::tileWidth<>;
  data.size.height = static_cast<float>(data.nRows) * glob::tileHeight<>;

  data.tileset = parse_tileset(stepMap.tilesets(), graphics);
  ++tilesetId;

  if (const auto* properties = stepMap.get_properties()) {
    assert(properties);
    assert(properties->has("id"));
    assert(properties->get("id").is<int>());
    assert(properties->has("humanoidLayer"));
    assert(properties->get("humanoidLayer").is<int>());

    data.id = properties->get("id").get<int>();
    data.humanoidLayer = properties->get("humanoidLayer").get<int>();
  }

  parse_layers(stepMap, data);

  return data;
}

}  // namespace

auto parse_world(const std::filesystem::path& world, graphics_context& graphics)
    -> ir::world
{
  const auto stepMap = std::make_unique<step::map>(world);
  const auto directory = std::filesystem::absolute(world).parent_path();

  ir::world data;
  data.base = parse_map(*stepMap, graphics);

  for (const auto& object : data.base.objects) {
    if (object.portal) {
      const auto levelPath = directory / object.portal->path;
      const auto stepLevel = std::make_unique<step::map>(levelPath);
      data.levels.push_back(parse_map(*stepLevel, graphics));
    }
  }

  return data;
}

}  // namespace wanderer
