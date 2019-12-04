#pragma once
#include "tiled_animation.h"
#include <stdexcept>
#include <pugixml.hpp>
#include <string>
#include <map>
#include <vector>

namespace albinjohansson::tiled {

struct TilePropertyData {
  std::string name = "";
  std::string type = "";
  std::string value = "";
};

class TiledTileSet final {
 private:
  pugi::xml_node tileSetNode;
  std::map<int, TiledAnimation> animations;
  std::map<int, std::vector<TilePropertyData>> propertyData;
  const int firstId;
  const int lastId;

  void Init();

  void ProcessAnimation(int tileId);

  void ProcessProperties(int tileId, const pugi::xml_node& tileNode);

  void ProcessObjectGroup(int tileId);

  [[nodiscard]] const TilePropertyData& GetData(int tileId, const std::string& name) const;

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

  /**
   * Indicates whether or not the tile associated with the supplied ID has a property with the
   * specified name.
   *
   * @param tileId the ID of the tile to check.
   * @param name the name of the property to look for.
   * @return true if the tile has a property with the specified name; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool HasProperty(int tileId, const std::string& name) const noexcept;

  /**
   * Attempts to find a boolean property for a tile and return its value.
   *
   * @param tileId the ID of the tile that owns the boolean property.
   * @param name the name of the boolean property.
   * @return the boolean value of the specified property; false if the property isn't found.
   * @since 0.1.0
   */
  [[nodiscard]] bool GetBool(int tileId, const std::string& name) const;

  /**
   * Attempts to find an integer property for a tile and return its value.
   *
   * @param tileId the ID of the tile that owns the integer property.
   * @param name the name of the integer property.
   * @return the integer value of the specified property; 0 if the property isn't found.
   * @since 0.1.0
   */
  [[nodiscard]] int GetInt(int tileId, const std::string& name) const;

  /**
   * Attempts to find a float property for a tile and return its value.
   *
   * @param tileId the ID of the tile that owns the float property.
   * @param name the name of the float property.
   * @return the float value of the specified property; 0 if the property isn't found.
   * @since 0.1.0
   */
  [[nodiscard]] float GetFloat(int tileId, const std::string& name) const;

  /**
   * Attempts to find a string property for a tile and return its value.
   *
   * @param tileId the ID of the tile that owns the string property.
   * @param name the name of the string property.
   * @return the string value of the specified property; the empty string is returned if the
   * property isn't found.
   * @since 0.1.0
   */
  [[nodiscard]] std::string GetString(int tileId, const std::string& name) const;
//  /**
//   * Attempts to obtain a property of the tile with the specified ID.
//   *
//   * @tparam T the type of the value in the property.
//   * @param tileId the ID of the tile that owns the desired property.
//   * @param name the name of the property to look for.
//   * @return a tiled property.
//   * @throws invalid_argument if the there are no properties for the tile associated with the
//   * supplied ID, or if the specified type isn't supported.
//   * @since 0.1.0
//   */
//  template<typename T>
//  [[nodiscard]] TiledProperty<T> GetProperty(int tileId, const std::string& name) const {
//    if (propertyData.count(tileId)) {
//      std::vector<TilePropertyData> properties = propertyData.at(tileId);
//
//      for (TilePropertyData data : properties) {
//        // TODO does not support "color and "file"
//        if (data.type == "bool") {
//          return TiledProperty<T>(data.name, data.value == "true");
//        } else if (data.type == "int") {
//          return TiledProperty<T>(data.name, std::stoi(data.value));
//        } else if (data.type == "float") {
//          return TiledProperty<T>(data.name, std::stof(data.value));
//        }
////        else if (data.type == "string") {
////          return TiledProperty<T>(data.name, data.value);
////        }
//      }
//
//      throw std::invalid_argument("Failed to obtain property: " + name
//                                      + ", for tile with ID: " + std::to_string(tileId));
//    }
//
//    throw std::invalid_argument("Found no properties for tile: " + std::to_string(tileId));
//  }
};

}
