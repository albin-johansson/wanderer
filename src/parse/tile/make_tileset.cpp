#include "make_tileset.h"

#include "animated.h"
#include "make_tile.h"
#include "math.h"
#include "tileset.h"

using namespace centurion;

namespace wanderer {

entt::entity make_tileset(entt::registry& registry,
                          const std::vector<step::Tileset>& tilesets,
                          Renderer& renderer)
{
  const auto entity = registry.create();

  auto& tileset = registry.emplace<Tileset>(entity);

  for (const auto& stepTileset : tilesets) {
    for (auto index = 0, id = stepTileset.first_gid();
         index < stepTileset.tile_count();
         ++index, ++id) {
      const auto [row, col] =
          Math::index_to_matrix_pos(index, stepTileset.columns());

      const IRect src{
          {col * stepTileset.tile_width(), row * stepTileset.tile_height()},
          {stepTileset.tile_width(), stepTileset.tile_height()}};

      const auto tileEntity = make_basic_tile(
          registry,
          static_cast<TileID>(id),
          Texture::shared(renderer,
                          ("resource/map/" + stepTileset.image()).c_str()),
          src);

      tileset.tiles.emplace(id, tileEntity);
    }

    for (const auto& stepTile : stepTileset.tiles()) {
      const auto gid =
          static_cast<TileID>(stepTileset.first_gid() + stepTile.id());
      parse_special_tile(registry,
                         tileset.tiles.at(gid),
                         stepTile,
                         static_cast<TileID>(stepTileset.first_gid()));
    }
  }

  return entity;
}

}  // namespace wanderer
