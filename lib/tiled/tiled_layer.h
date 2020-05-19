#pragma once
#include <vector>
#include <string>
#include <pugixml.hpp>
#include "tiled_object.h"

namespace tiled {

class TiledLayer final {
 private:
  int nRows = 0;
  int nCols = 0;
  int nNonEmptyTiles = 0;
  pugi::xml_node layerNode;
  std::vector<int> tiles;
  std::vector<TiledObject> properties;

 public:
  explicit TiledLayer(const pugi::xml_node& layerNode);

  ~TiledLayer();

  [[nodiscard]]
  std::vector<int> get_tiles() const;

  [[nodiscard]]
  int get_int(const std::string& id) const;

  [[nodiscard]]
  bool get_bool(const std::string& id) const;

  [[nodiscard]]
  int get_non_empty_tiles() const noexcept;

  [[nodiscard]]
  int get_rows() const noexcept;

  [[nodiscard]]
  int get_cols() const noexcept;
};

}
