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
    ProcessAnimation(id, tileNode);
    ProcessProperties(id, tileNode);
    ProcessObjectGroup(id, tileNode);
  }
}

void TiledTileSet::ProcessAnimation(int tileId, const pugi::xml_node& tileNode) {
  for (auto animationNode : tileNode.children("animation")) {

    const int nFrames = std::distance(animationNode.children("frame").begin(),
                                      animationNode.children("frame").end());
    TiledAnimation animation(nFrames);

    int index = 0;
    for (auto frameNode : animationNode.children("frame")) {
      const int frameId = firstId + frameNode.attribute("tileid").as_int();
      const int duration = frameNode.attribute("duration").as_int();

      Frame frame = {frameId, duration};

      animation.AddFrame(index, frame);
      ++index;
    }

    animations.insert(std::pair<int, TiledAnimation>(tileId, animation));
  }
}

void TiledTileSet::ProcessProperties(int tileId, const pugi::xml_node& tileNode) {
  for (auto propertiesNode : tileNode.children("properties")) {

    std::vector<TilePropertyData> properties;
    for (auto propertyNode : propertiesNode.children("property")) {
      std::string name = propertyNode.attribute("name").as_string();
      std::string type = propertyNode.attribute("type").as_string();
      std::string value = propertyNode.attribute("value").as_string();
      TilePropertyData data = {name, type, value};

      properties.push_back(data);
    }

    propertyData.insert(std::pair<int, std::vector<TilePropertyData>>(tileId, properties));
  }
}

void TiledTileSet::ProcessObjectGroup(int tileId, const pugi::xml_node& tileNode) {
  pugi::xml_node groupNode = tileNode.child("objectgroup");
  for (auto objectNode : groupNode.children("object")) {

    TiledObject object;
    for (auto attribute : objectNode.attributes()) {
      object.AddAttribute(attribute.name(), attribute.value());
    }

    objects.insert(std::pair<int, TiledObject>(tileId, object));
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

bool TiledTileSet::HasProperty(int tileId, const std::string& name) const noexcept {
  if (propertyData.count(tileId)) {
    for (const auto& data : propertyData.at(tileId)) {
      if (data.name == name) {
        return true;
      }
    }
  }
  return false;
}

const TilePropertyData& TiledTileSet::GetData(int tileId, const std::string& name) const {
  if (propertyData.count(tileId)) {
    for (const auto& data : propertyData.at(tileId)) {
      if (data.name == name) {
        return data;
      }
    }
  }
  throw std::invalid_argument("Failed to obtain tile data for " + std::to_string(tileId));
}

bool TiledTileSet::GetBool(int tileId, const std::string& name) const {
  if (propertyData.count(tileId)) {
    auto& data = GetData(tileId, name);
    if (data.value == "bool") {
      return data.value == "true";
    }
  }
  return false;
}

int TiledTileSet::GetInt(int tileId, const std::string& name) const {
  if (propertyData.count(tileId)) {
    return std::stoi(GetData(tileId, name).value);
  }

  return 0;
}

float TiledTileSet::GetFloat(int tileId, const std::string& name) const {
  if (propertyData.count(tileId)) {
    return std::stof(GetData(tileId, name).value);
  }

  return 0;
}

std::string TiledTileSet::GetString(int tileId, const std::string& name) const {
  if (propertyData.count(tileId)) {
    return GetData(tileId, name).value;
  }

  return "";
}

bool TiledTileSet::HasAnimation(int tileId) const noexcept {
  return animations.count(tileId);
}

TiledAnimation TiledTileSet::GetAnimation(int tileId) const {
  return animations.at(tileId);
}

bool TiledTileSet::HasObject(int tileId) const noexcept {
  return objects.count(tileId);
}

TiledObject TiledTileSet::GetObject(int tileId) const {
  return objects.at(tileId);
}

}
