#include "make_map.hpp"

#include <step_map.hpp>
#include <vector>

#include "depth_drawable.hpp"
#include "game_constants.hpp"
#include "make_tileset.hpp"
#include "math_utils.hpp"
#include "tile_layer.hpp"
#include "tilemap.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto create_tile_matrix(const int nRows, const int nCols)
    -> comp::TileLayer::tile_matrix
{
  const auto rows = static_cast<std::size_t>(nRows);
  const auto cols = static_cast<std::size_t>(nCols);
  return {rows, std::vector<tile_id>(cols, g_emptyTile)};
}

[[nodiscard]] auto create_ground_layer(entt::registry& registry,
                                       const step::layer& stepLayer,
                                       const step::tile_layer& stepTileLayer)
    -> comp::TileLayer::entity
{
  const auto groundLayerEntity = registry.create();

  auto& tileLayer = registry.emplace<comp::TileLayer>(groundLayerEntity);
  tileLayer.matrix = create_tile_matrix(stepLayer.height(), stepLayer.width());

  int index = 0;
  for (const auto gid : stepTileLayer.data()->as_gid()) {
    const auto [row, col] = Math::index_to_matrix_pos(index, stepLayer.width());

    const auto r = static_cast<std::size_t>(row);
    const auto c = static_cast<std::size_t>(col);
    tileLayer.matrix.at(r).at(c) = gid.get();
    ++index;
  }

  return comp::TileLayer::entity{groundLayerEntity};
}

void create_tile_objects(entt::registry& registry,
                         comp::tilemap& tilemap,
                         const step::layer& stepLayer,
                         const std::vector<step::global_id>& tileData,
                         const comp::tileset& tileset)
{
  int index = 0;
  for (const auto gid : tileData) {
    if (gid.get() == g_emptyTile) {
      ++index;
      continue;
    }

    const auto& tile =
        registry.get<comp::Tile>(tileset.tiles.at(gid.get()).get());
    const auto tileObjectEntity = registry.create();
    const auto [row, col] = Math::index_to_matrix_pos(index, stepLayer.width());
    const auto tileSize = g_tileSize<float>;

    auto& drawable = registry.emplace<comp::DepthDrawable>(tileObjectEntity);
    drawable.texture = tile.sheet;
    drawable.src = tile.src;

    drawable.dst = {{static_cast<float>(col) * tileSize,
                     static_cast<float>(row) * tileSize},
                    {tileSize, tileSize}};

    drawable.depth = depth{5};  // FIXME
    drawable.centerY =
        (static_cast<float>(row) * tileSize) + (drawable.dst.height() / 2.0f);

    tilemap.tileObjects.emplace(comp::MapPosition{row, col}, tileObjectEntity);

    ++index;
  }

  // TODO load actual game objects (items, NPCs, portals to other levels)
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
    const auto* layerProps = stepLayer.get_properties();

    if (stepLayer.is<step::tile_layer>()) {
      const auto& stepTileLayer = stepLayer.as<step::tile_layer>();

      if (layerProps->has("ground")) {
        if (layerProps->is("ground", true)) {
          tilemap.layers.emplace_back(
              create_ground_layer(registry, stepLayer, stepTileLayer));
        } else {
          const auto& tileset =
              registry.get<comp::tileset>(tilemap.tileset.get());
          create_tile_objects(registry,
                              tilemap,
                              stepLayer,
                              stepTileLayer.data()->as_gid(),
                              tileset);
        }
      }

    } else if (stepLayer.is<step::object_group>()) {
      // TODO spawnpoints, etc.
    }
  }

  tilemap.layers.shrink_to_fit();

  return comp::tilemap::entity{mapEntity};
}

}  // namespace wanderer
