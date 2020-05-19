#pragma once
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "tiled_object.h"

namespace tiled {

class TiledLayer final {
 public:
  explicit TiledLayer(const pugi::xml_node& layerNode);

  ~TiledLayer();

  [[nodiscard]] std::vector<int> get_tiles() const;

  [[nodiscard]] int get_int(const std::string& id) const;

  [[nodiscard]] bool get_bool(const std::string& id) const;

  [[nodiscard]] int get_non_empty_tiles() const noexcept;

  [[nodiscard]] int get_rows() const noexcept;

  [[nodiscard]] int get_cols() const noexcept;

 private:
  int m_nRows = 0;
  int m_nCols = 0;
  int m_nNonEmptyTiles = 0;
  pugi::xml_node m_layerNode;
  std::vector<int> m_tiles;
  std::vector<TiledObject> m_properties;
};

}  // namespace tiled
