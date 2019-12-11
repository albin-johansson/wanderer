#pragma once
#include "tiled_property.h"
#include "tiled_object.h"
#include "tiled_animation.h"
#include <pugixml.hpp>
#include <vector>

namespace albinjohansson::tiled {

/**
 * The TiledTile class represents a tile in a Tiled tile set. A tile has an integer ID, an
 * (optional) animation and supports custom properties.
 *
 * @since 0.1.0
 */
class TiledTile final {
 private:
  pugi::xml_node tileNode;
  TiledAnimation animation;
  std::vector<TiledProperty> properties;
  std::vector<TiledObject> objects;
  const int id = 0;
  bool animated = false;

  void ProcessAnimation(int firstTileSetId);

  void ProcessProperties();

  void ProcessObjectGroup();

  /**
   * Attempts to find and return a property.
   *
   * @param name the name of the property to return.
   * @return the property with the specified name.
   * @throws invalid_argument if there is no property with the specified name.
   * @since 0.1.0
   */
  [[nodiscard]] const TiledProperty& GetProperty(const std::string& name) const;

 public:
  TiledTile(const pugi::xml_node& tileNode, int id, int firstTileSetId);

  ~TiledTile();

  /**
   * Returns the integer ID associated with the tile.
   *
   * @return the integer ID associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] int GetId() const noexcept;

  /**
   * Returns a reference to the animation associated with the tile.
   *
   * @return a reference to the animation associated with the tile.
   * @since 0.1.0
   */
  [[nodiscard]] const TiledAnimation& GetAnimation() const noexcept;

  [[nodiscard]] bool HasAttribute(const std::string& name) const noexcept;

  /**
   * Indicates whether or not the tile has a property with the specified name.
   *
   * @param name the name of the property to look for.
   * @return true if a property with the specified name is found; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool HasProperty(const std::string& name) const noexcept;

  /**
   * Indicates whether or not the tile has an object with the specified name.
   *
   * @param name the name of the object to look for.
   * @return true if a object with the specified name is found; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool HasObject(const std::string& name) const noexcept;

  /**
   * Returns the value of the property with the specified name as an integer. This method might
   * return unexpected values if the property doesn't represent an integer.
   *
   * @param name the name of the property to return the integer value of.
   * @return the value of the property with the specified name as an integer.
   * @throws invalid_argument if the property doesn't exist.
   * @since 0.1.0
   */
  [[nodiscard]] int GetIntProperty(const std::string& name) const;

  /**
   * Returns the value of the property with the specified name as a float. This method might
   * return unexpected values if the property doesn't represent a float.
   *
   * @param name the name of the property to return the float value of.
   * @return the value of the property with the specified name as a float.
   * @throws invalid_argument if the property doesn't exist.
   * @since 0.1.0
   */
  [[nodiscard]] float GetFloatProperty(const std::string& name) const;

  /**
   * Returns the value of the property with the specified name as a bool. This method might
   * return unexpected values if the property doesn't represent a bool. This method expects the
   * property value to be in all lower case, more specifically, the method checks whether or not
   * the property value is equal to the string "true".
   *
   * @param name the name of the property to return the bool value of.
   * @return the value of the property with the specified name as a bool.
   * @throws invalid_argument if the property doesn't exist.
   * @since 0.1.0
   */
  [[nodiscard]] bool GetBoolProperty(const std::string& name) const;

  /**
   * Returns the value of the property with the specified name as a string.
   *
   * @param name the name of the property to return the string value of.
   * @return the value of the property with the specified name as a string.
   * @throws invalid_argument if the property doesn't exist.
   * @since 0.1.0
   */
  [[nodiscard]] const std::string& GetStringProperty(const std::string& name) const;

  [[nodiscard]] int GetIntAttribute(const std::string& name) const;

  [[nodiscard]] std::string GetStringAttribute(const std::string& name) const;

  /**
   * Returns the object with the specified name.
   *
   * @param name the name of the object to look for.
   * @return the object with the specified name.
   * @throws invalid_argument if the object doesn't exist.
   * @since 0.1.0
   */
  [[nodiscard]] const TiledObject& GetObject(const std::string& name) const;

  /**
   * Indicates whether or not the tile is animated.
   *
   * @return true if the tile is animated; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsAnimated() const noexcept;
};

}
