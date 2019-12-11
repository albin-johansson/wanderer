#pragma once
#include "tiled_animation.h"
#include "tiled_object.h"
#include "tiled_tile.h"
#include "tiled_object.h"
#include <stdexcept>
#include <pugixml.hpp>
#include <string>
#include <unordered_map>

namespace albinjohansson::tiled {

class TiledTileSet final {
 private:
  pugi::xml_node tileSetNode;
  std::unordered_map<int, TiledTile> tiles;
  const int firstId;
  const int lastId;

  void Init();

 public:
  /**
   * @param tileSetNode the root tile set node.
   * @param firstId the first valid tile id.
   * @param lastId the last valid tile id.
   * @since 0.1.0
   */
  TiledTileSet(pugi::xml_node tileSetNode, int firstId, int lastId);

  /**
   * @param tileSetNode the root tile set node.
   * @param firstId the first valid tile id.
   * @param lastId the last valid tile id.
   * @since 0.1.0
   */
  TiledTileSet(pugi::xml_node&& tileSetNode, int firstId, int lastId);

  ~TiledTileSet();

  /**
   * Returns the name of the tile set.
   *
   * @return the name of the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] std::string GetName() const;

  /**
   * Returns the width of all tiles in the tile set.
   *
   * @return the width of all tiles in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetTileWidth() const;

  /**
   * Returns the height of all tiles in the tile set.
   *
   * @return the height of all tiles in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetTileHeight() const;

  /**
   * Returns the total amount of tiles in the tile set.
   *
   * @return the total amount of tiles in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetTileCount() const;

  /**
   * Returns the amount of columns in the tile set.
   *
   * @return the amount of columns in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetCols() const;

  /**
   * Returns the image source path for the image associated with the tile set.
   *
   * @return the image source path for the image associated with the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] std::string GetImageSource() const;

  [[nodiscard]] std::string GetImageName() const;

  /**
   * Returns the width of the image associated with the tile set.
   *
   * @return the width of the image associated with the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetImageWidth() const;

  /**
   * Returns the height of the image associated with the tile set.
   *
   * @return the height of the image associated with the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetImageHeight() const;

  /**
   * Returns the first valid tile ID in the tile set.
   *
   * @return the first valid tile ID in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetFirstTileId() const noexcept { return firstId; }

  /**
   * Returns the last valid tile ID in the tile set.
   *
   * @return the last valid tile ID in the tile set.
   * @since 0.1.0
   */
  [[nodiscard]] int GetLastTileId() const noexcept { return lastId; }

  [[nodiscard]] bool HasTile(int id) const noexcept;

  [[nodiscard]] const TiledTile& GetTile(int id) const;
};

}
