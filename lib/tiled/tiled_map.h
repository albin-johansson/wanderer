#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <pugixml.hpp>
#include "tiled_layer.h"
#include "tiled_object_group.h"

namespace albinjohansson::tiled {

class TiledMap final {
 private:
  pugi::xml_node mapNode;
  std::vector<std::unique_ptr<TiledLayer>> layers;
  std::vector<std::unique_ptr<TiledObjectGroup>> tiledObjectGroups;

  void init();

 public:
  explicit TiledMap(pugi::xml_node mapNode);

  explicit TiledMap(pugi::xml_node&& mapNode);

  ~TiledMap();

  [[nodiscard]]
  int get_width() const;

  [[nodiscard]]
  int get_height() const;

  [[nodiscard]]
  int get_tile_width() const;

  [[nodiscard]]
  int get_tile_height() const;

  [[nodiscard]]
  int get_amount_of_layers() const;

  [[nodiscard]]
  float convert_x(float x, float tileSize) const noexcept;

  [[nodiscard]]
  float convert_y(float y, float tileSize) const noexcept;

  [[nodiscard]]
  const std::vector<std::unique_ptr<TiledLayer>>& get_layers() const;

  [[nodiscard]]
  const std::vector<std::unique_ptr<TiledObjectGroup>>& get_tiled_object_groups() const;

};

}
