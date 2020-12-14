#include "parse_map.hpp"

#include <cassert>    // assert
#include <stdexcept>  // runtime_error
#include <step_map.hpp>
#include <step_tile_layer.hpp>
#include <vector>  // vector

#include "add_tile_objects.hpp"
#include "game_constants.hpp"
#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "index_to_matrix.hpp"
#include "make_tileset.hpp"
#include "maybe.hpp"
#include "portal.hpp"
#include "spawnpoint.hpp"
#include "tile_layer.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_tile_matrix(const int nRows, const int nCols)
    -> comp::tile_layer::tile_matrix
{
  const auto rows = static_cast<std::size_t>(nRows);
  const auto cols = static_cast<std::size_t>(nCols);
  return {rows, std::vector<tile_id>(cols, g_emptyTile)};
}

void add_ground_layer(entt::registry& registry,
                      const step::tile_layer& tileLayer,
                      const int numRows,
                      const int numColumns,
                      const int layerIndex)
{
  const comp::tile_layer::entity entity{registry.create()};

  auto& layer = registry.emplace<comp::tile_layer>(entity);
  layer.matrix = make_tile_matrix(numRows, numColumns);
  layer.z = layerIndex;

  int index{0};
  for (const auto gid : tileLayer.data()->as_gid()) {
    const auto [row, col] = index_to_matrix<std::size_t>(index, numColumns);
    layer.matrix.at(row).at(col) = tile_id{gid.get()};
    ++index;
  }
}

void parse_tile_layer(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const step::tile_layer& layer,
                      const step::properties* properties,
                      const int index)
{
  assert(properties);
  assert(properties->has("ground"));
  assert(properties->get("ground").is<bool>());

  if (properties->is("ground", true)) {
    add_ground_layer(registry, layer, tilemap.rows, tilemap.cols, index);
  } else {
    if (const auto* data = layer.data()) {
      const auto& tileset = registry.get<comp::tileset>(tilemap.tileset);
      add_tile_objects(registry, tilemap, tileset, data->as_gid(), index);
    }
  }
}

[[nodiscard]] auto get_spawnpoint_entity(const step::properties& props)
{
  if (props.is("entity", "player")) {
    return comp::spawnpoint_type::player;
  } else if (props.is("entity", "skeleton")) {
    return comp::spawnpoint_type::skeleton;
  } else {
    throw std::runtime_error{"Did not recognize spawnpoint type!"};
  }
}

void parse_spawnpoint(entt::registry& registry, const step::object& object)
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("entity"));
  assert(props->get("entity").is<std::string>());

  const vector2f position{static_cast<float>(object.x()),
                          static_cast<float>(object.y())};

  registry.emplace<comp::spawnpoint>(registry.create(),
                                     get_spawnpoint_entity(*props),
                                     position);
}

[[nodiscard]] auto make_portal_hitbox(const step::object& object)
    -> comp::hitbox
{
  const cen::farea size{static_cast<float>(object.width()),
                        static_cast<float>(object.height())};
  const comp::subhitbox subhitbox{{}, size};

  auto hitbox = sys::hitbox::create({subhitbox});
  hitbox.enabled = false;

  const vector2f pos{static_cast<float>(object.x()),
                     static_cast<float>(object.y())};
  sys::hitbox::set_position(hitbox, pos);

  return hitbox;
}

void parse_portal(entt::registry& registry, const step::object& object)
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("target"));
  assert(props->get("target").is<int>());
  assert(props->has("path"));
  assert(props->get("path").is<step::file>());

  const auto entity = registry.create();

  auto& portal = registry.emplace<comp::portal>(entity);
  portal.target = map_id{props->get("target").get<int>()};
  portal.path = props->get("path").get<step::file>().get();

  registry.emplace<comp::hitbox>(entity, make_portal_hitbox(object));
}

void parse_object_group(entt::registry& registry,
                        const step::object_group& group)
{
  for (const auto& object : group.objects()) {
    if (object.type() == "Spawnpoint") {
      parse_spawnpoint(registry, object);
    } else if (object.type() == "Portal") {
      parse_portal(registry, object);
    }
  }
}

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
      parse_object_group(registry, *group);
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

  tilemap.width = static_cast<float>(stepMap.width()) * g_tileSize<float>;
  tilemap.height = static_cast<float>(stepMap.height()) * g_tileSize<float>;
  tilemap.rows = stepMap.height();
  tilemap.cols = stepMap.width();
  tilemap.tileset = make_tileset(registry, stepMap.tilesets(), graphics);

  return tilemap;
}

}  // namespace

auto parse_map(entt::registry& registry,
               const step::fs::path& path,
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
