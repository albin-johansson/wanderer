#pragma once
#include "tiled_layer.h"
#include "tiled_object_group.h"
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
  std::vector<std::unique_ptr<TiledObjectGroup>> tiledObjectGroups;

  void Init();

 public:
  explicit TiledMap(pugi::xml_node mapNode);

  explicit TiledMap(pugi::xml_node&& mapNode);

  ~TiledMap();

  [[nodiscard]] int GetWidth() const;

  [[nodiscard]] int GetHeight() const;

  [[nodiscard]] int GetTileWidth() const;

  [[nodiscard]] int GetTileHeight() const;

  [[nodiscard]] int GetAmountOfLayers() const;

  [[nodiscard]] float ConvertX(float x, float tileSize) const noexcept;

  [[nodiscard]] float ConvertY(float y, float tileSize) const noexcept;

  [[nodiscard]] const std::vector<std::unique_ptr<TiledLayer>>& GetLayers() const;

  [[nodiscard]] const std::vector<std::unique_ptr<TiledObjectGroup>>& GetTiledObjectGroups() const;

};

}
