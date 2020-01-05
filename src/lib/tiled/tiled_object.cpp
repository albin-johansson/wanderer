#include "tiled_object.h"
#include <stdexcept>

namespace albinjohansson::tiled {

TiledObject::TiledObject() = default;

TiledObject::~TiledObject() = default;

void TiledObject::add_attribute(const std::string& id, const std::string& value) {
  attributes.emplace(id, value);
}

void TiledObject::add_property(const TiledProperty& property) {
  properties.push_back(property);
}

const std::string& TiledObject::get_attribute(const std::string& id) const {
  return attributes.at(id);
}

bool TiledObject::has_attribute(const std::string& id) const {
  return attributes.count(id);
}

const TiledProperty& TiledObject::get_property(const std::string& id) const {
  for (const auto& property : properties) {
    if (property.name == id) {
      return property;
    }
  }

  throw std::invalid_argument("Failed to find property " + id);
}

bool TiledObject::has_property(const std::string& id) const noexcept {
  for (const auto& property : properties) {
    if (property.name == id) {
      return true;
    }
  }
  return false;
}

const std::vector<TiledProperty>& TiledObject::get_properties() const noexcept {
  return properties;
}

}
