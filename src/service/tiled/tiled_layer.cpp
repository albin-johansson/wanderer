#include "tiled_layer.h"
#include <sstream>
#include <iostream>

namespace albinjohansson::tiled {

TiledLayer::TiledLayer(const pugi::xml_node& layerNode) : layerNode(layerNode) {
  nCols = layerNode.attribute("width").as_int();
  nRows = layerNode.attribute("height").as_int();
  tiles.reserve(nRows * nCols);

  auto data = layerNode.child("data").text().as_string();

  for (auto propertiesNode : layerNode.children("properties")) {
    for (auto propertyNode : propertiesNode.children("property")) {
      TiledObject object;

      const auto id = propertyNode.attribute("name").value();
      const auto value = propertyNode.attribute("value").value();

      object.AddAttribute(id, value);

      properties.push_back(object);
    }
  }

  std::stringstream stream(data);
  std::string token;
  while (std::getline(stream, token, ',')) {
    const auto i = std::stoi(token);
    tiles.push_back(i);

    if (i != 0) {
      ++nNonEmptyTiles;
    }
  }
}

TiledLayer::~TiledLayer() = default;

std::vector<int> TiledLayer::GetTiles() const {
  return tiles;
}

int TiledLayer::GetInt(const std::string& id) const {
  for (auto& property : properties) {
    if (property.HasAttribute(id)) {
      return std::stoi(property.GetAttribute(id));
    }
  }

  std::cout << "Failed to find layer property: " << id.c_str() << "\n";
  return 0;
}

bool TiledLayer::GetBool(const std::string& id) const {
  for (auto& property : properties) {
    if (property.HasAttribute(id)) {
      return property.GetAttribute(id) == "true";
    }
  }

  std::cout << "Failed to find layer property: " << id.c_str() << "\n";
  return false;
}

int TiledLayer::GetNonEmptyTiles() const noexcept {
  return nNonEmptyTiles;
}

int TiledLayer::GetRows() const noexcept {
  return nRows;
}

int TiledLayer::GetCols() const noexcept {
  return nCols;
}

}

