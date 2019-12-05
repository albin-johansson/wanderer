#include "tiled_tile_set.h"
#include <string>

namespace albinjohansson::tiled {

TiledTileSet::TiledTileSet(pugi::xml_node tileSetNode, int firstId, int lastId)
    : tileSetNode(tileSetNode), firstId(firstId), lastId(lastId) {
  Init();
}

TiledTileSet::TiledTileSet(pugi::xml_node&& tileSetNode, int firstId, int lastId)
    : tileSetNode(tileSetNode), firstId(firstId), lastId(lastId) {
  Init();
}

TiledTileSet::~TiledTileSet() = default;

void TiledTileSet::Init() {
  for (auto tileNode : tileSetNode.children("tile")) {
    const int id = firstId + tileNode.attribute("id").as_int();

    // TODO could be replace by vector, alg. for finding tile is then: id -> t.at(id - firstId)
    tiles.insert(std::pair<int, TiledTile>(id, TiledTile(tileNode, id, firstId)));
  }
}

std::string TiledTileSet::GetName() const {
  return tileSetNode.attribute("name").as_string();
}

int TiledTileSet::GetTileWidth() const {
  return tileSetNode.attribute("tilewidth").as_int();
}

int TiledTileSet::GetTileHeight() const {
  return tileSetNode.attribute("tileheight").as_int();
}

int TiledTileSet::GetTileCount() const {
  return tileSetNode.attribute("tilecount").as_int();
}

int TiledTileSet::GetCols() const {
  return tileSetNode.attribute("columns").as_int();
}

std::string TiledTileSet::GetImageSource() const {
  return tileSetNode.child("image").attribute("source").as_string();
}

std::string TiledTileSet::GetImageName() const {
  std::string source = GetImageSource();
  return source.substr(source.find_last_of('/') + 1);
}

int TiledTileSet::GetImageWidth() const {
  return tileSetNode.child("image").attribute("width").as_int();
}

int TiledTileSet::GetImageHeight() const {
  return tileSetNode.child("image").attribute("height").as_int();
}

bool TiledTileSet::HasTile(int id) const noexcept {
  return tiles.count(id);
}

const TiledTile& TiledTileSet::GetTile(int id) const {
  return tiles.at(id);
}

}
