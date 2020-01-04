#include "tile_builder.h"
#include "tiled_tile_set.h"
#include "image.h"
#include "game_constants.h"

using namespace centurion;

namespace albinjohansson::wanderer {

TileAnimation TileBuilder::create_animation(tiled::TiledAnimation animation) {
  const auto& frames = animation.GetFrames();
  TileAnimation result{static_cast<int>(frames.size())};

  int i = 0;
  for (const auto frame : frames) {
    result.set_frame(i, {static_cast<TileID>(frame.tileId), static_cast<uint32_t>(frame.duration)});
    ++i;
  }

  return result;
}

Tile TileBuilder::create(const std::shared_ptr<Image>& image,
                         const tiled::TiledTileSet& tiledTileSet,
                         TileID id,
                         int index) {
  Tile tile;

  tile.sheet = image;
  tile.id = id;

  const auto tileWidth = tiledTileSet.GetTileWidth();
  const auto tileHeight = tiledTileSet.GetTileHeight();

  if (tiledTileSet.HasTile(id)) {
    const auto& tiledTile = tiledTileSet.GetTile(id);

    if (tiledTile.HasProperty("depth")) {
      tile.set_depth(tiledTile.GetIntProperty("depth"));
    }

    if (tiledTile.HasAttribute("type")) {
      tile.isObject = tiledTile.GetStringAttribute("type") == "Object";
    }

    if (tiledTile.IsAnimated()) {
      tile.animation = create_animation(tiledTile.GetAnimation());
      tile.isAnimated = true;
    }

    if (tiledTile.HasObject("hitbox")) {
      const auto& object = tiledTile.GetObject("hitbox");

      const auto x = (std::stof(object.GetAttribute("x")) / tileWidth) * tileSize;
      const auto y = (std::stof(object.GetAttribute("y")) / tileHeight) * tileSize;
      const auto w = (std::stof(object.GetAttribute("width")) / tileWidth) * tileSize;
      const auto h = (std::stof(object.GetAttribute("height")) / tileHeight) * tileSize;

      tile.hitbox.add_rectangle(FRectangle{x, y, Area{w, h}}, Vector2{x, y});
      tile.isBlocked = true;
    }
  }

  const auto[row, col] = MathUtils::index_to_matrix_pos(index, tiledTileSet.GetCols());
  const int x = col * tileWidth;
  const int y = row * tileHeight;

  tile.source = {x, y, tileWidth, tileHeight};

  return tile;
}

}
