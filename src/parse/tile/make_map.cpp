#include "make_map.h"

#include <step.h>

#include <vector>

#include "game_constants.h"
#include "make_tileset.h"
#include "math_utils.h"
#include "tile_layer.h"
#include "tilemap.h"

using centurion::Renderer;

namespace wanderer {
namespace {

[[nodiscard]] TileLayer::TileMatrix create_tile_matrix(const int nRows,
                                                       const int nCols)
{
  const auto rows = static_cast<std::size_t>(nRows);
  const auto cols = static_cast<std::size_t>(nCols);
  return {rows, std::vector<TileID>(cols, g_emptyTile)};
}

[[nodiscard]] TileLayerEntity create_ground_layer(
    entt::registry& registry,
    const step::Layer& stepLayer,
    const step::TileLayer& stepTileLayer)
{
  const auto groundLayerEntity = registry.create();

  auto& tileLayer = registry.emplace<TileLayer>(groundLayerEntity);
  tileLayer.nRows = stepLayer.height();
  tileLayer.nCols = stepLayer.width();
  tileLayer.matrix = create_tile_matrix(tileLayer.nRows, tileLayer.nCols);

  int index = 0;
  for (const auto gid : stepTileLayer.data().as_gid()) {
    const auto [row, col] = Math::index_to_matrix_pos(index, tileLayer.nCols);

    const auto r = static_cast<std::size_t>(row);
    const auto c = static_cast<std::size_t>(col);
    tileLayer.matrix.at(r).at(c) = gid;
    ++index;
  }

  return TileLayerEntity{groundLayerEntity};
}

[[nodiscard]] TileLayerEntity create_object_layer(entt::registry& registry)
{
  const auto objectLayerEntity = registry.create();

  // TODO load actual game objects (items, NPCs, portals to other levels)

  return TileLayerEntity{objectLayerEntity};
}

}  // namespace

TilemapEntity make_map(entt::registry& registry,
                      std::string_view map,
                      Renderer& renderer,
                      ImageCache& imageCache)
{
  const auto stepMap = step::parse("resource/map/", map);
  const auto mapEntity = registry.create();

  auto& tilemap = registry.emplace<Tilemap>(mapEntity);
  tilemap.width = static_cast<float>(stepMap->width()) * g_tileSize<float>;
  tilemap.height = static_cast<float>(stepMap->height()) * g_tileSize<float>;
  tilemap.rows = stepMap->height();
  tilemap.cols = stepMap->width();
  tilemap.tileset =
      make_tileset(registry, stepMap->tilesets(), renderer, imageCache);

  for (const auto& stepLayer : stepMap->layers()) {
    const auto& layerProps = stepLayer.properties();

    if (stepLayer.is_tile_layer()) {
      const auto& stepTileLayer = stepLayer.as_tile_layer();

      if (layerProps.has("ground")) {
        if (layerProps.is("ground", true)) {
          tilemap.groundLayers.emplace_back(
              create_ground_layer(registry, stepLayer, stepTileLayer));
        } else {
          tilemap.objectLayers.emplace_back(create_object_layer(registry));
        }
      }

    } else if (stepLayer.is_object_group()) {
      // TODO spawnpoints, etc.
    }
  }

  return TilemapEntity{mapEntity};
}

}  // namespace wanderer
