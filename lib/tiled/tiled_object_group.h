#pragma once
#include <vector>
#include <pugixml.hpp>
#include "tiled_object.h"

namespace tiled {

class TiledObjectGroup final {
 private:
  pugi::xml_node objectGroupNode;
  std::vector<TiledObject> objects;

 public:
  explicit TiledObjectGroup(pugi::xml_node objectGroupNode);

  ~TiledObjectGroup();

  [[nodiscard]]
  const std::vector<TiledObject>& get_objects() const noexcept;
};

}
