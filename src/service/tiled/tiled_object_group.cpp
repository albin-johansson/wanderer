#include "tiled_object_group.h"
#include "tiled_object.h"
#include "tiled_property.h"

namespace albinjohansson::tiled {

TiledObjectGroup::TiledObjectGroup(pugi::xml_node objectGroupNode)
    : objectGroupNode(objectGroupNode) {

  for (const auto o : objectGroupNode.children("object")) {
    TiledObject object;

    for (const auto attribute : o.attributes()) {
      object.AddAttribute(attribute.name(), attribute.value());
    }

    const auto propertiesNode = o.child("properties");
    for (const auto p : propertiesNode.children("property")) {
      TiledProperty property;
      property.name = p.attribute("name").as_string();
      property.value = p.attribute("value").as_string();
      object.AddProperty(property);
    }

    objects.push_back(object);
  }
}

TiledObjectGroup::~TiledObjectGroup() = default;

const std::vector<TiledObject>& TiledObjectGroup::GetObjects() const noexcept {
  return objects;
}

}
