#pragma once
#include "tiled_layer.h"
#include <pugixml.hpp>
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace albinjohansson::tiled {

class TiledMap final {
 private:
  pugi::xml_node mapNode;
  std::vector<std::unique_ptr<TiledLayer>> layers;

 public:
  explicit TiledMap(pugi::xml_node mapNode);

  explicit TiledMap(pugi::xml_node&& mapNode);

  ~TiledMap();

  [[nodiscard]] int GetWidth() const;

  [[nodiscard]] int GetHeight() const;

  [[nodiscard]] int GetTileWidth() const;

  [[nodiscard]] int GetTileHeight() const;

  [[nodiscard]] int GetAmountOfLayers() const;

  [[nodiscard]] const std::vector<std::unique_ptr<TiledLayer>>& GetLayers() const;

};

}
