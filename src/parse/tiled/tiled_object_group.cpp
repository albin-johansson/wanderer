#include "tiled_object_group.h"

#include "tiled_object.h"
#include "tiled_property.h"

namespace tiled {

TiledObjectGroup::TiledObjectGroup(pugi::xml_node objectGroupNode)
    : m_objectGroupNode(objectGroupNode)
{
  for (const auto o : objectGroupNode.children("object")) {
    TiledObject object;

    for (const auto attribute : o.attributes()) {
      object.add_attribute(attribute.name(), attribute.value());
    }

    const auto propertiesNode = o.child("properties");
    for (const auto p : propertiesNode.children("property")) {
      TiledProperty property;
      property.name = p.attribute("name").as_string();
      property.value = p.attribute("value").as_string();
      object.add_property(property);
    }

    m_objects.push_back(object);
  }
}

TiledObjectGroup::~TiledObjectGroup() = default;

const std::vector<TiledObject>& TiledObjectGroup::get_objects() const noexcept
{
  return m_objects;
}

}  // namespace tiled
