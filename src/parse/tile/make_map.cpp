#include "make_map.h"

#include <step.h>

#include <vector>

#include "depth_drawable.h"
#include "game_constants.h"
#include "make_tileset.h"
#include "math_utils.h"
#include "tile_layer.h"
#include "tilemap.h"

using ctn::Renderer;

using namespace wanderer::component;

namespace wanderer {
namespace {

[[nodiscard]] auto create_tile_matrix(const int nRows, const int nCols)
    -> TileLayer::TileMatrix
{
  const auto rows = static_cast<std::size_t>(nRows);
  const auto cols = static_cast<std::size_t>(nCols);
  return {rows, std::vector<TileID>(cols, g_emptyTile)};
}

[[nodiscard]] auto create_ground_layer(entt::registry& registry,
                                       const step::Layer& stepLayer,
                                       const step::TileLayer& stepTileLayer)
    -> TileLayerEntity
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

void create_tile_objects(entt::registry& registry,
                         Tilemap& tilemap,
                         const step::Layer& stepLayer,
                         const std::vector<step::GID>& tileData,
                         const Tileset& tileset)
{
  int index = 0;
  for (const auto gid : tileData) {
    if (gid == g_emptyTile) {
      ++index;
      continue;
    }

    const auto& tile = registry.get<Tile>(tileset.tiles.at(gid).get());

    const auto tileObjectEntity = registry.create();

    const auto [row, col] = Math::index_to_matrix_pos(index, stepLayer.width());

    const auto tileSize = g_tileSize<float>;

    auto& drawable = registry.emplace<DepthDrawable>(tileObjectEntity);
    drawable.texture = tile.sheet;
    drawable.src = tile.src;

    drawable.dst = {{static_cast<float>(col) * tileSize,
                     static_cast<float>(row) * tileSize},
                    {tileSize, tileSize}};

    drawable.depth = Depth{5};  // FIXME
    drawable.centerY =
        (static_cast<float>(row) * tileSize) + (drawable.dst.height() / 2.0f);

    tilemap.tileObjects.emplace(MapPosition{row, col}, tileObjectEntity);

    ++index;
  }

  // TODO load actual game objects (items, NPCs, portals to other levels)
}

}  // namespace

auto make_map(entt::registry& registry,
              std::string_view map,
              Renderer& renderer,
              ImageCache& imageCache) -> TilemapEntity
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
          const auto& tileset = registry.get<Tileset>(tilemap.tileset.get());
          create_tile_objects(registry,
                              tilemap,
                              stepLayer,
                              stepTileLayer.data().as_gid(),
                              tileset);
        }
      }

    } else if (stepLayer.is_object_group()) {
      // TODO spawnpoints, etc.
    }
  }

  tilemap.groundLayers.shrink_to_fit();

  return TilemapEntity{mapEntity};
}

}  // namespace wanderer
