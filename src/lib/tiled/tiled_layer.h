#pragma once
#include "tiled_object.h"
#include <vector>
#include <pugixml.hpp>
#include <string>

namespace albinjohansson::tiled {

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
