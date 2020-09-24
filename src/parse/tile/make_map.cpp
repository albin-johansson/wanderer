#include "make_map.hpp"

#include <step_map.hpp>
#include <step_tile_layer.hpp>
#include <vector>

#include "add_tile_objects.hpp"
#include "component/tile_layer.hpp"
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

[[nodiscard]] auto make_ground_layer(entt::registry& registry,
                                     const step::tile_layer& tileLayer,
                                     int numRows,
                                     int numColumns) -> comp::tile_layer::entity
{
  const auto layerEntity = registry.create();

  auto& layer = registry.emplace<comp::tile_layer>(layerEntity);
  layer.matrix = make_tile_matrix(numRows, numColumns);

  int index{0};
  for (const auto gid : tileLayer.data()->as_gid()) {
    const auto [row, col] = index_to_matrix<std::size_t>(index, numColumns);
    layer.matrix.at(row).at(col) = gid.get();
    ++index;
  }

  return comp::tile_layer::entity{layerEntity};
}

void parse_tile_layer(entt::registry& registry,
                      comp::tilemap& tilemap,
                      const step::tile_layer& layer,
                      const step::properties* properties)
{
  if (properties->has("ground")) {
    if (properties->is("ground", true)) {
      tilemap.layers.emplace_back(
          make_ground_layer(registry, layer, tilemap.rows, tilemap.cols));
    } else {
      const auto& tileset = registry.get<comp::tileset>(tilemap.tileset.get());
      if (const auto* data = layer.data()) {
        const auto& gid = data->as_gid();
        add_tile_objects(registry, tilemap, tileset, gid.begin(), gid.end());
      }
    }
  }
}

}  // namespace

auto make_map(entt::registry& registry,
              const step::fs::path& path,
              cen::renderer& renderer,
              image_cache& imageCache) -> comp::tilemap::entity
{
  const auto stepMap = std::make_unique<step::map>(path);
  const auto mapEntity = registry.create();

  auto& tilemap = registry.emplace<comp::tilemap>(mapEntity);
  tilemap.width = static_cast<float>(stepMap->width()) * g_tileSize<float>;
  tilemap.height = static_cast<float>(stepMap->height()) * g_tileSize<float>;
  tilemap.rows = stepMap->height();
  tilemap.cols = stepMap->width();
  tilemap.tileset =
      make_tileset(registry, stepMap->tilesets(), renderer, imageCache);

  for (const auto& stepLayer : stepMap->layers()) {
    const auto* properties = stepLayer.get_properties();

    if (const auto* tileLayer = stepLayer.try_as<step::tile_layer>()) {
      parse_tile_layer(registry, tilemap, *tileLayer, properties);
    } else if (const auto* group = stepLayer.try_as<step::object_group>()) {
      // TODO spawnpoints, etc.
    }
  }

  tilemap.layers.shrink_to_fit();

  return comp::tilemap::entity{mapEntity};
}

}  // namespace wanderer
