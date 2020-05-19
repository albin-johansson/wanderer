#pragma once
#include <pugixml.hpp>
#include <vector>

#include "tiled_object.h"

namespace tiled {

class TiledObjectGroup final {
 public:
  explicit TiledObjectGroup(pugi::xml_node objectGroupNode);

  ~TiledObjectGroup();

  [[nodiscard]] const std::vector<TiledObject>& get_objects() const noexcept;

 private:
  pugi::xml_node m_objectGroupNode;
  std::vector<TiledObject> m_objects;
};

}  // namespace tiled
