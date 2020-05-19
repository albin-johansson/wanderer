#include "tiled_tile.h"
#include <stdexcept>

namespace tiled {

TiledTile::TiledTile(const pugi::xml_node& tileNode, int id, int firstTileSetId)
    : tileNode(tileNode), id(id) {
  process_animation(firstTileSetId);
  process_properties();
  process_object_groups();
}

TiledTile::~TiledTile() = default;

void TiledTile::process_animation(int firstTileSetId) {
  for (const auto animationNode : tileNode.children("animation")) {

    auto index = 0;
    for (const auto frameNode : animationNode.children("frame")) {
      const auto frameId = firstTileSetId + frameNode.attribute("tileid").as_int();
      const auto duration = frameNode.attribute("duration").as_int();

      animation.add_frame(Frame{frameId, duration});
      ++index;
    }
  }

  animated = !animation.get_frames().empty();
}

void TiledTile::process_properties() {
  const auto propertiesNode = tileNode.child("properties");
  for (const auto propertyNode : propertiesNode.children("property")) {
    const auto name = propertyNode.attribute("name").as_string();
    const auto type = propertyNode.attribute("type").as_string();
    const auto value = propertyNode.attribute("value").as_string();

    properties.push_back(TiledProperty{name, type, value});
  }
}

void TiledTile::process_object_groups() {
  const auto objectGroupNode = tileNode.child("objectgroup");
  for (const auto objectNode : objectGroupNode.children("object")) {
    TiledObject object;
    for (const auto attribute : objectNode.attributes()) {
      object.add_attribute(attribute.name(), attribute.value());
    }
    objects.push_back(object);
  }
}

int TiledTile::get_id() const noexcept {
  return id;
}

const TiledAnimation& TiledTile::get_animation() const noexcept {
  return animation;
}

bool TiledTile::has_attribute(const std::string& name) const noexcept {
  return !tileNode.attribute(name.c_str()).empty();
}

bool TiledTile::has_property(const std::string& name) const noexcept {
  for (const auto& property : properties) {
    if (property.name == name) {
      return true;
    }
  }
  return false;
}

bool TiledTile::has_object(const std::string& name) const noexcept {
  for (const auto& object : objects) {
    if (object.get_attribute("name") == name) { // may theoretically throw, but shouldn't
      return true;
    }
  }

  return false;
}

const TiledProperty& TiledTile::get_property(const std::string& name) const {
  for (const auto& property : properties) {
    if (property.name == name) {
      return property;
    }
  }

  const auto msg = "Failed to find property: " + name + ", in tile " + std::to_string(id);
  throw std::invalid_argument(msg);
}

int TiledTile::get_int_property(const std::string& name) const {
  return std::stoi(get_property(name).value);
}

float TiledTile::get_float_property(const std::string& name) const {
  return std::stof(get_property(name).value);
}

bool TiledTile::get_bool_property(const std::string& name) const {
  return get_property(name).value == "true";
}

const std::string& TiledTile::get_string_property(const std::string& name) const {
  return get_property(name).value;
}

int TiledTile::get_int_attribute(const std::string& name) const {
  return tileNode.attribute(name.c_str()).as_int();
}

std::string TiledTile::get_string_attribute(const std::string& name) const {
  return tileNode.attribute(name.c_str()).as_string();
}

const TiledObject& TiledTile::get_object(const std::string& name) const {
  for (const auto& object : objects) {
    if (object.get_attribute("name") == name) {
      return object;
    }
  }

  const auto msg = "Failed to find object with name: " + name + ", in tile " + std::to_string(id);
  throw std::invalid_argument(msg);
}

bool TiledTile::is_animated() const noexcept {
  return animated;
}

}
