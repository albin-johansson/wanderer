#include "make_map.hpp"

#include <cassert>   // assert
#include <optional>  // optional
#include <step_map.hpp>
#include <step_tile_layer.hpp>
#include <vector>  // vector

#include "add_tile_objects.hpp"
#include "component/spawnpoint.hpp"
#include "game_constants.hpp"
#include "index_to_matrix.hpp"
#include "make_tileset.hpp"

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
                      int numRows,
                      int numColumns,
                      int zIndex)
{
  const auto layerEntity = registry.create();

  auto& layer = registry.emplace<comp::tile_layer>(layerEntity);
  layer.matrix = make_tile_matrix(numRows, numColumns);
  layer.z = zIndex;

  int index{0};
  for (const auto gid : tileLayer.data()->as_gid()) {
    const auto [row, col] = index_to_matrix<std::size_t>(index, numColumns);
    layer.matrix.at(row).at(col) = gid.get();
    ++index;
  }
}

void parse_tile_layer(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const step::tile_layer& layer,
                      const step::properties* properties,
                      int zIndex)
{
  assert(properties->has("ground"));
  assert(properties->get("ground").is<bool>());

  if (properties->is("ground", true)) {
    add_ground_layer(registry, layer, tilemap.rows, tilemap.cols, zIndex);
  } else {
    if (const auto* data = layer.data()) {
      const auto& gid = data->as_gid();
      const auto& tileset = registry.get<comp::tileset>(tilemap.tileset.get());
      add_tile_objects(registry, tilemap, tileset, gid.begin(), gid.end());
    }
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

  std::optional<comp::spawnpoint_type> type;
  if (props->is("entity", "player")) {
    type = comp::spawnpoint_type::player;

  } else if (props->is("entity", "skeleton")) {
    type = comp::spawnpoint_type::skeleton;
  }

  registry.emplace<comp::spawnpoint>(registry.create(), type.value(), position);
}

void parse_object_group(entt::registry& registry,
                        const step::object_group& group)
{
  for (const auto& object : group.objects()) {
    if (object.type() == "spawnpoint") {
      parse_spawnpoint(registry, object);
    }
  }
}

void parse_layers(entt::registry& registry,
                  comp::tilemap& tilemap,
                  const std::vector<step::layer>& layers)
{
  int zIndex{0};  // Assumes that the layers are in the correct order
  for (const auto& stepLayer : layers) {
    const auto* properties = stepLayer.get_properties();

    if (const auto* tileLayer = stepLayer.try_as<step::tile_layer>()) {
      parse_tile_layer(registry, tilemap, *tileLayer, properties, zIndex);
    } else if (const auto* group = stepLayer.try_as<step::object_group>()) {
      parse_object_group(registry, *group);
    }

    ++zIndex;
  }

  // Ensures that the layers are stored in the correct order in the registry
  registry.sort<comp::tile_layer>(
      [](const comp::tile_layer& lhs, const comp::tile_layer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

}  // namespace

auto make_map(entt::registry& registry,
              const step::fs::path& path,
              cen::renderer& renderer,
              texture_cache& imageCache) -> comp::tilemap::entity
{
  const auto stepMap = std::make_unique<step::map>(path);
  const comp::tilemap::entity mapEntity{registry.create()};

  auto& tilemap = registry.emplace<comp::tilemap>(mapEntity.get());
  tilemap.width = static_cast<float>(stepMap->width()) * g_tileSize<float>;
  tilemap.height = static_cast<float>(stepMap->height()) * g_tileSize<float>;
  tilemap.rows = stepMap->height();
  tilemap.cols = stepMap->width();
  tilemap.tileset =
      make_tileset(registry, stepMap->tilesets(), renderer, imageCache);

  parse_layers(registry, tilemap, stepMap->layers());

  return mapEntity;
}

}  // namespace wanderer
