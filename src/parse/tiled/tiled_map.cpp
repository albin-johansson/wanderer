#include "tiled_map.h"

#include "tiled_object_group.h"

namespace tiled {

TiledMap::TiledMap(pugi::xml_node mapNode) : m_mapNode(mapNode)
{
  init();
}

TiledMap::TiledMap(pugi::xml_node&& mapNode) : m_mapNode(mapNode)
{
  init();
}

TiledMap::~TiledMap() = default;

void TiledMap::init()
{
  for (auto layerNode : m_mapNode.children("layer")) {
    m_layers.push_back(std::make_unique<TiledLayer>(layerNode));
  }

  for (auto objectGroupNode : m_mapNode.children("objectgroup")) {
    m_tiledObjectGroups.push_back(
        std::make_unique<TiledObjectGroup>(objectGroupNode));
  }
}

int TiledMap::get_width() const
{
  return m_mapNode.attribute("width").as_int();
}

int TiledMap::get_height() const
{
  return m_mapNode.attribute("height").as_int();
}

int TiledMap::get_tile_width() const
{
  return m_mapNode.attribute("tilewidth").as_int();
}

int TiledMap::get_tile_height() const
{
  return m_mapNode.attribute("tileheight").as_int();
}

int TiledMap::get_amount_of_layers() const
{
  return static_cast<int>(m_layers.size());
}

float TiledMap::convert_x(float x, float tileSize) const noexcept
{
  return (x / static_cast<float>(get_tile_width())) * tileSize;
}

float TiledMap::convert_y(float y, float tileSize) const noexcept
{
  return (y / static_cast<float>(get_tile_height())) * tileSize;
}

const std::vector<std::unique_ptr<TiledLayer>>& TiledMap::get_layers() const
{
  return m_layers;
}

const std::vector<std::unique_ptr<TiledObjectGroup>>&
TiledMap::get_tiled_object_groups() const
{
  return m_tiledObjectGroups;
}

}  // namespace tiled
