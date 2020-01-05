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

      object.add_attribute(id, value);

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

std::vector<int> TiledLayer::get_tiles() const {
  return tiles;
}

int TiledLayer::get_int(const std::string& id) const {
  for (auto& property : properties) {
    if (property.has_attribute(id)) {
      return std::stoi(property.get_attribute(id));
    }
  }

  std::cout << "Failed to find layer property: " << id.c_str() << "\n";
  return 0;
}

bool TiledLayer::get_bool(const std::string& id) const {
  for (auto& property : properties) {
    if (property.has_attribute(id)) {
      return property.get_attribute(id) == "true";
    }
  }

  std::cout << "Failed to find layer property: " << id.c_str() << "\n";
  return false;
}

int TiledLayer::get_non_empty_tiles() const noexcept {
  return nNonEmptyTiles;
}

int TiledLayer::get_rows() const noexcept {
  return nRows;
}

int TiledLayer::get_cols() const noexcept {
  return nCols;
}

}

