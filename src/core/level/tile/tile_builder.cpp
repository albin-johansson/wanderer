#include "tile_builder.h"

#include "game_constants.h"

using namespace centurion;

namespace albinjohansson::wanderer {

TileAnimation TileBuilder::create_animation(tiled::TiledAnimation animation)
{
  const auto& frames = animation.get_frames();
  TileAnimation result{static_cast<int>(frames.size())};

  int i = 0;
  for (const auto frame : frames) {
    result.set_frame(i,
                     {static_cast<TileID>(frame.tileId),
                      static_cast<uint32_t>(frame.duration)});
    ++i;
  }

  return result;
}

Tile TileBuilder::create(const std::shared_ptr<Texture>& image,
                         const tiled::TiledTileSet& tiledTileSet,
                         TileID id,
                         int index)
{
  Tile tile;

  tile.sheet = image;
  tile.id = id;

  const auto tileWidth = tiledTileSet.get_tile_width();
  const auto tileHeight = tiledTileSet.get_tile_height();

  if (tiledTileSet.has_tile(id)) {
    const auto& tiledTile = tiledTileSet.get_tile(id);

    if (tiledTile.has_property("depth")) {
      tile.set_depth(tiledTile.get_int_property("depth"));
    }

    if (tiledTile.has_attribute("type")) {
      tile.isObject = tiledTile.get_string_attribute("type") == "Object";
    }

    if (tiledTile.is_animated()) {
      tile.animation = create_animation(tiledTile.get_animation());
      tile.isAnimated = true;
    }

    const auto tile_size = GameConstants::tile_size;
    if (tiledTile.has_object("hitbox")) {
      const auto& object = tiledTile.get_object("hitbox");

      const auto x =
          (std::stof(object.get_attribute("x")) / tileWidth) * tile_size;
      const auto y =
          (std::stof(object.get_attribute("y")) / tileHeight) * tile_size;
      const auto w =
          (std::stof(object.get_attribute("width")) / tileWidth) * tile_size;
      const auto h =
          (std::stof(object.get_attribute("height")) / tileHeight) * tile_size;

      tile.hitbox.add_rectangle(FRect{x, y, w, h}, Vector2{x, y});
      tile.isBlocked = true;
    }
  }

  const auto [row, col] =
      Math::index_to_matrix_pos(index, tiledTileSet.get_cols());
  const int x = col * tileWidth;
  const int y = row * tileHeight;

  tile.source = {x, y, tileWidth, tileHeight};

  return tile;
}

}  // namespace albinjohansson::wanderer
