#pragma once
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "tiled_object.h"

namespace tiled {

class TiledLayer final {
 public:
  enum class Type { TileLayer, ObjectGroup, ImageLayer, Group };

  explicit TiledLayer(const pugi::xml_node& layerNode);

  ~TiledLayer();

  [[nodiscard]] std::vector<int> tiles() const;

  [[nodiscard, deprecated]] int get_int(const std::string& id) const;

  [[nodiscard, deprecated]] bool get_bool(const std::string& id) const;

  [[nodiscard]] int width() const noexcept { return m_width; }

  [[nodiscard]] int height() const noexcept { return m_height; }

  [[nodiscard]] int populated_tiles() const noexcept
  {
    return m_nPopulatedTiles;
  }

 private:
  int m_width = 0;   // actually the number of columns
  int m_height = 0;  // actually the number of rows
  int m_nPopulatedTiles = 0;
  std::vector<int> m_tiles;
  std::vector<TiledObject> m_properties;
  Type m_type;
  bool m_visible;
};

}  // namespace tiled
