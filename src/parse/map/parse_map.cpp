#include "parse_map.hpp"

#include <cassert>  // assert
#include <step_map.hpp>

#include "add_tile_objects.hpp"
#include "game_constants.hpp"
#include "inventory.hpp"
#include "make_tileset.hpp"
#include "parse_object_layer.hpp"
#include "parse_tile_layer.hpp"
#include "portal.hpp"
#include "tile_layer.hpp"

namespace wanderer {
namespace {

void parse_layers(entt::registry& registry,
                  comp::tilemap& tilemap,
                  const std::vector<step::layer>& layers)
{
  int index{0};
  for (const auto& stepLayer : layers) {
    const auto* props = stepLayer.get_properties();

    if (const auto* tileLayer = stepLayer.try_as<step::tile_layer>()) {
      parse_tile_layer(registry, tilemap, *tileLayer, props, index);

    } else if (const auto* group = stepLayer.try_as<step::object_group>()) {
      parse_object_layer(registry, *group);
    }

    ++index;
  }

  // Ensures that the layers are stored in the correct order in the registry
  registry.sort<comp::tile_layer>(
      [](const comp::tile_layer& lhs, const comp::tile_layer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

auto make_tilemap(entt::registry& registry,
                  const comp::tilemap::entity mapEntity,
                  const step::map& stepMap,
                  graphics_context& graphics) -> comp::tilemap&
{
  auto& tilemap = registry.emplace<comp::tilemap>(mapEntity);

  tilemap.width = static_cast<float>(stepMap.width()) * glob::tileWidth<>;
  tilemap.height = static_cast<float>(stepMap.height()) * glob::tileHeight<>;
  tilemap.rows = stepMap.height();
  tilemap.cols = stepMap.width();
  tilemap.tileset = make_tileset(registry, stepMap.tilesets(), graphics);

  return tilemap;
}

}  // namespace

auto parse_map(entt::registry& registry,
               const std::filesystem::path& path,
               graphics_context& graphics) -> comp::tilemap::entity
{
  const auto stepMap = std::make_unique<step::map>(path);

  const comp::tilemap::entity mapEntity{registry.create()};
  auto& tilemap = make_tilemap(registry, mapEntity, *stepMap, graphics);

  if (const auto* props = stepMap->get_properties()) {
    assert(props);
    assert(props->has("id"));
    assert(props->get("id").is<int>());
    assert(props->has("humanoidLayer"));
    assert(props->get("humanoidLayer").is<int>());
    tilemap.id = map_id{props->get("id").get<int>()};
    tilemap.humanoidLayer = props->get("humanoidLayer").get<int>();
  }

  parse_layers(registry, tilemap, stepMap->layers());

  return mapEntity;
}

}  // namespace wanderer
