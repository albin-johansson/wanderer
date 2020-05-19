#include "tiled_tile_set.h"
#include <string>

namespace tiled {

TiledTileSet::TiledTileSet(pugi::xml_node tileSetNode, int firstId, int lastId)
    : tileSetNode(tileSetNode), firstId(firstId), lastId(lastId) {
  init();
}

TiledTileSet::TiledTileSet(pugi::xml_node&& tileSetNode, int firstId, int lastId)
    : tileSetNode(tileSetNode), firstId(firstId), lastId(lastId) {
  init();
}

TiledTileSet::~TiledTileSet() = default;

void TiledTileSet::init() {
  for (auto tileNode : tileSetNode.children("tile")) {
    const int id = firstId + tileNode.attribute("id").as_int();
    // TODO could be replace by vector, alg. for finding tile is then: id -> t.at(id - firstId)
    tiles.emplace(id, TiledTile(tileNode, id, firstId));
  }
}

std::string TiledTileSet::get_name() const {
  return tileSetNode.attribute("name").as_string();
}

int TiledTileSet::get_tile_width() const {
  return tileSetNode.attribute("tilewidth").as_int();
}

int TiledTileSet::get_tile_height() const {
  return tileSetNode.attribute("tileheight").as_int();
}

int TiledTileSet::get_tile_count() const {
  return tileSetNode.attribute("tilecount").as_int();
}

int TiledTileSet::get_cols() const {
  return tileSetNode.attribute("columns").as_int();
}

std::string TiledTileSet::get_image_source() const {
  return tileSetNode.child("image").attribute("source").as_string();
}

std::string TiledTileSet::get_image_name() const {
  std::string source = get_image_source();
  return source.substr(source.find_last_of('/') + 1);
}

int TiledTileSet::get_image_width() const {
  return tileSetNode.child("image").attribute("width").as_int();
}

int TiledTileSet::get_image_height() const {
  return tileSetNode.child("image").attribute("height").as_int();
}

bool TiledTileSet::has_tile(int id) const noexcept {
  return tiles.count(id);
}

const TiledTile& TiledTileSet::get_tile(int id) const {
  return tiles.at(id);
}

}
