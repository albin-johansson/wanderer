#include "tiled_map.h"

namespace albinjohansson::tiled {

TiledMap::TiledMap(pugi::xml_node mapNode) : mapNode(mapNode) {
  // TODO check if name seems to be correct
}

TiledMap::TiledMap(pugi::xml_node&& mapNode) : mapNode(mapNode) {

}

TiledMap::~TiledMap() = default;

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

}
