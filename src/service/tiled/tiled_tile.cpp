#include "tiled_tile.h"
#include <stdexcept>

namespace albinjohansson::tiled {

TiledTile::TiledTile(const pugi::xml_node& tileNode, int id, int firstTileSetId)
    : tileNode(tileNode), id(id) {
  ProcessAnimation(firstTileSetId);
  ProcessProperties();
  ProcessObjectGroup();
}

TiledTile::~TiledTile() = default;

void TiledTile::ProcessAnimation(int firstTileSetId) {
  for (const auto animationNode : tileNode.children("animation")) {

    auto index = 0;
    for (const auto frameNode : animationNode.children("frame")) {
      const auto frameId = firstTileSetId + frameNode.attribute("tileid").as_int();
      const auto duration = frameNode.attribute("duration").as_int();

      animation.AddFrame(Frame{frameId, duration});
      ++index;
    }
  }

  animated = !animation.GetFrames().empty();
}

void TiledTile::ProcessProperties() {
  const auto propertiesNode = tileNode.child("properties");
  for (const auto propertyNode : propertiesNode.children("property")) {
    const auto name = propertyNode.attribute("name").as_string();
    const auto type = propertyNode.attribute("type").as_string();
    const auto value = propertyNode.attribute("value").as_string();

    properties.push_back(TiledProperty{name, type, value});
  }
}

void TiledTile::ProcessObjectGroup() {
  const auto objectGroupNode = tileNode.child("objectgroup");
  for (const auto objectNode : objectGroupNode.children("object")) {
    TiledObject object;
    for (const auto attribute : objectNode.attributes()) {
      object.AddAttribute(attribute.name(), attribute.value());
    }
    objects.push_back(object);
  }
}

int TiledTile::GetId() const noexcept {
  return id;
}

const TiledAnimation& TiledTile::GetAnimation() const noexcept {
  return animation;
}

bool TiledTile::HasAttribute(const std::string& name) const noexcept {
  return !tileNode.attribute(name.c_str()).empty();
}

bool TiledTile::HasProperty(const std::string& name) const noexcept {
  for (const auto& property : properties) {
    if (property.name == name) {
      return true;
    }
  }
  return false;
}

bool TiledTile::HasObject(const std::string& name) const noexcept {
  for (const auto& object : objects) {
    if (object.GetAttribute("name") == name) { // may theoretically throw, but shouldn't
      return true;
    }
  }

  return false;
}

const TiledProperty& TiledTile::GetProperty(const std::string& name) const {
  for (const auto& property : properties) {
    if (property.name == name) {
      return property;
    }
  }

  const auto msg = "Failed to find property: " + name + ", in tile " + std::to_string(id);
  throw std::invalid_argument(msg);
}

int TiledTile::GetIntProperty(const std::string& name) const {
  return std::stoi(GetProperty(name).value);
}

float TiledTile::GetFloatProperty(const std::string& name) const {
  return std::stof(GetProperty(name).value);
}

bool TiledTile::GetBoolProperty(const std::string& name) const {
  return GetProperty(name).value == "true";
}

const std::string& TiledTile::GetStringProperty(const std::string& name) const {
  return GetProperty(name).value;
}

int TiledTile::GetIntAttribute(const std::string& name) const {
  return tileNode.attribute(name.c_str()).as_int();
}

std::string TiledTile::GetStringAttribute(const std::string& name) const {
  return tileNode.attribute(name.c_str()).as_string();
}

const TiledObject& TiledTile::GetObject(const std::string& name) const {
  for (const auto& object : objects) {
    if (object.GetAttribute("name") == name) {
      return object;
    }
  }

  const auto msg = "Failed to find object with name: " + name + ", in tile " + std::to_string(id);
  throw std::invalid_argument(msg);
}

bool TiledTile::IsAnimated() const noexcept {
  return animated;
}

}
