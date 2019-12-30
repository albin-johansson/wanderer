#include "tiled_map.h"
#include "tiled_object_group.h"

namespace albinjohansson::tiled {

TiledMap::TiledMap(pugi::xml_node mapNode) : mapNode(mapNode) {
  Init();
}

TiledMap::TiledMap(pugi::xml_node&& mapNode) : mapNode(mapNode) {
  Init();
}

TiledMap::~TiledMap() = default;

void TiledMap::Init() {
  for (auto layerNode : mapNode.children("layer")) {
    layers.push_back(std::make_unique<TiledLayer>(layerNode));
  }

  for (auto objectGroupNode : mapNode.children("objectgroup")) {
    tiledObjectGroups.push_back(std::make_unique<TiledObjectGroup>(objectGroupNode));
  }
}

int TiledMap::GetWidth() const {
  return mapNode.attribute("width").as_int();
}

int TiledMap::GetHeight() const {
  return mapNode.attribute("height").as_int();
}

int TiledMap::GetTileWidth() const {
  return mapNode.attribute("tilewidth").as_int();
}

int TiledMap::GetTileHeight() const {
  return mapNode.attribute("tileheight").as_int();
}

int TiledMap::GetAmountOfLayers() const {
  return layers.size();
}

float TiledMap::ConvertX(float x, float tileSize) const noexcept {
  return (x / static_cast<float>(GetTileWidth())) * tileSize;
}

float TiledMap::ConvertY(float y, float tileSize) const noexcept {
  return (y / static_cast<float>(GetTileHeight())) * tileSize;
}

const std::vector<std::unique_ptr<TiledLayer>>& TiledMap::GetLayers() const {
  return layers;
}

const std::vector<std::unique_ptr<TiledObjectGroup>>& TiledMap::GetTiledObjectGroups() const {
  return tiledObjectGroups;
}

}
