#pragma once
#include "tiled_object.h"
#include "pugixml.hpp"
#include <vector>

namespace albinjohansson::tiled {

class TiledObjectGroup final {
 private:
  pugi::xml_node objectGroupNode;
  std::vector<TiledObject> objects;

 public:
  explicit TiledObjectGroup(pugi::xml_node objectGroupNode);

  ~TiledObjectGroup();

  [[nodiscard]]
  const std::vector<TiledObject>& GetObjects() const noexcept;
};

}
