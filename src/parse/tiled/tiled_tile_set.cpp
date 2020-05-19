#include "tiled_tile_set.h"

#include <string>

namespace tiled {

TiledTileSet::TiledTileSet(pugi::xml_node tileSetNode, int firstId, int lastId)
    : m_tileSetNode(tileSetNode), m_firstId(firstId), m_lastId(lastId)
{
  init();
}

TiledTileSet::TiledTileSet(pugi::xml_node&& tileSetNode,
                           int firstId,
                           int lastId)
    : m_tileSetNode(tileSetNode), m_firstId(firstId), m_lastId(lastId)
{
  init();
}

TiledTileSet::~TiledTileSet() = default;

void TiledTileSet::init()
{
  for (auto tileNode : m_tileSetNode.children("tile")) {
    const int id = m_firstId + tileNode.attribute("id").as_int();
    // TODO could be replace by vector, alg. for finding tile is then: id ->
    // t.at(id - firstId)
    m_tiles.emplace(id, TiledTile(tileNode, id, m_firstId));
  }
}

std::string TiledTileSet::get_name() const
{
  return m_tileSetNode.attribute("name").as_string();
}

int TiledTileSet::get_tile_width() const
{
  return m_tileSetNode.attribute("tilewidth").as_int();
}

int TiledTileSet::get_tile_height() const
{
  return m_tileSetNode.attribute("tileheight").as_int();
}

int TiledTileSet::get_tile_count() const
{
  return m_tileSetNode.attribute("tilecount").as_int();
}

int TiledTileSet::get_cols() const
{
  return m_tileSetNode.attribute("columns").as_int();
}

std::string TiledTileSet::get_image_source() const
{
  return m_tileSetNode.child("image").attribute("source").as_string();
}

std::string TiledTileSet::get_image_name() const
{
  std::string source = get_image_source();
  return source.substr(source.find_last_of('/') + 1);
}

int TiledTileSet::get_image_width() const
{
  return m_tileSetNode.child("image").attribute("width").as_int();
}

int TiledTileSet::get_image_height() const
{
  return m_tileSetNode.child("image").attribute("height").as_int();
}

bool TiledTileSet::has_tile(int id) const noexcept
{
  return m_tiles.count(id);
}

const TiledTile& TiledTileSet::get_tile(int id) const
{
  return m_tiles.at(id);
}

}  // namespace tiled
