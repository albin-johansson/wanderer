#include "tiled_layer.h"

#include <iostream>
#include <sstream>

namespace tiled {

TiledLayer::TiledLayer(const pugi::xml_node& layerNode)
//: m_layerNode(layerNode)
{
  m_width = layerNode.attribute("width").as_int();
  m_height = layerNode.attribute("height").as_int();
  m_tiles.reserve(m_height * m_width);

  auto data = layerNode.child("data").text().as_string();

  for (auto propertiesNode : layerNode.children("properties")) {
    for (auto propertyNode : propertiesNode.children("property")) {
      TiledObject object;

      const auto id = propertyNode.attribute("name").value();
      const auto value = propertyNode.attribute("value").value();

      object.add_attribute(id, value);

      m_properties.push_back(object);
    }
  }

  std::stringstream stream(data);
  std::string token;
  while (std::getline(stream, token, ',')) {
    const auto i = std::stoi(token);
    m_tiles.push_back(i);

    if (i != 0) {
      ++m_nPopulatedTiles;
    }
  }
}

TiledLayer::~TiledLayer() = default;

std::vector<int> TiledLayer::tiles() const
{
  return m_tiles;
}

int TiledLayer::get_int(const std::string& id) const
{
  for (auto& property : m_properties) {
    if (property.has_attribute(id)) {
      return std::stoi(property.get_attribute(id));
    }
  }

  std::cout << "Failed to find layer property: " << id.c_str() << "\n";
  return 0;
}

bool TiledLayer::get_bool(const std::string& id) const
{
  for (auto& property : m_properties) {
    if (property.has_attribute(id)) {
      return property.get_attribute(id) == "true";
    }
  }

  std::cout << "Failed to find layer property: " << id.c_str() << "\n";
  return false;
}

}  // namespace tiled
