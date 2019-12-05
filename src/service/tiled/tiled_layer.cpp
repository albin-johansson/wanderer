#include "tiled_layer.h"
#include <sstream>

#include <SDL.h>

namespace albinjohansson::tiled {

TiledLayer::TiledLayer(const pugi::xml_node& layerNode) : layerNode(layerNode) {
  const auto nCols = layerNode.attribute("width").as_int();
  const auto nRows = layerNode.attribute("height").as_int();
  tiles.reserve(nRows * nCols);

  auto data = layerNode.child("data").text().as_string();

  for (auto propertiesNode : layerNode.children("properties")) {
    for (auto propertyNode : propertiesNode.children("property")) {
      TiledObject object;

      const auto id = propertyNode.attribute("name").value();
      const auto value = propertyNode.attribute("value").value();

      int i;
      object.AddAttribute(id, value);

      properties.push_back(object);
    }
  }

  std::stringstream stream(data);
  std::string token;
  while (std::getline(stream, token, ',')) {
    tiles.push_back(std::stoi(token));
  }
}

TiledLayer::~TiledLayer() = default;

std::vector<int> TiledLayer::GetTiles() const {
  return tiles;
}

bool TiledLayer::GetBool(const std::string& id) const {
  for (auto& property : properties) {
    if (property.HasAttribute(id)) {
      return property.GetAttribute(id) == "true";
    }
  }

  SDL_Log("Failed to find layer property: %s", id.c_str());
  return false;
}

}

