#include "tile_builder.h"
#include "tiled_tile_set.h"
#include "image.h"

namespace albinjohansson::wanderer {

TileBuilder::TileBuilder() = default;

TileBuilder::~TileBuilder() = default;

TileAnimation TileBuilder::CreateAnimation(tiled::TiledAnimation animation) {
  const auto& frames = animation.GetFrames();
  TileAnimation result(frames.size());

  int i = 0;
  for (const auto frame : frames) {
    result.SetFrame(i, {static_cast<TileID>(frame.tileId), static_cast<uint32_t>(frame.duration)});
    ++i;
  }

  return result;
}

Tile TileBuilder::Create(const std::shared_ptr<Image>& image,
                         const tiled::TiledTileSet& tiledTileSet,
                         TileID id,
                         int index) const {
  Tile tile;

  tile.SetSheet(image);
  tile.SetId(id);

  const auto tileWidth = tiledTileSet.GetTileWidth();
  const auto tileHeight = tiledTileSet.GetTileHeight();

  if (tiledTileSet.HasTile(id)) {
    const auto& tiledTile = tiledTileSet.GetTile(id);

    if (tiledTile.HasProperty("depth")) {
      tile.SetDepth(tiledTile.GetIntProperty("depth"));
    }

    if (tiledTile.HasAttribute("type")) {
      tile.SetObject(tiledTile.GetStringAttribute("type") == "Object");
    }

    if (tiledTile.IsAnimated()) {
      tile.SetAnimation(CreateAnimation(tiledTile.GetAnimation()));
      tile.SetAnimated(true);
    }

    if (tiledTile.HasObject("hitbox")) {
      const auto& object = tiledTile.GetObject("hitbox");

      const auto x = (std::stof(object.GetAttribute("x")) / tileWidth) * Tile::SIZE;
      const auto y = (std::stof(object.GetAttribute("y")) / tileHeight) * Tile::SIZE;
      const auto w = (std::stof(object.GetAttribute("width")) / tileWidth) * Tile::SIZE;
      const auto h = (std::stof(object.GetAttribute("height")) / tileHeight) * Tile::SIZE;

      tile.AddRectangle(FRectangle(x, y, w, h), Vector2(x, y));
      tile.SetBlocked(true);
    }
  }

  const auto pos = MathUtils::IndexToMatrixPos(index, tiledTileSet.GetCols());
  const int x = pos.second * tileWidth;
  const int y = pos.first * tileHeight;

  tile.SetSource(Rectangle(x, y, tileWidth, tileHeight));

  return tile;
}

}