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
  pugi::xml_node layerNode;
  std::vector<int> tiles;
  std::vector<TiledObject> properties;

 public:
  explicit TiledLayer(const pugi::xml_node& layerNode);

  ~TiledLayer();

  [[nodiscard]] std::vector<int> GetTiles() const;

  [[nodiscard]] int GetInt(const std::string& id) const;

  [[nodiscard]] bool GetBool(const std::string& id) const;

  [[nodiscard]] int GetRows() const noexcept;

  [[nodiscard]] int GetCols() const noexcept;
};

}
