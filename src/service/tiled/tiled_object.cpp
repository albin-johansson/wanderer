#include "tiled_object.h"
#include <stdexcept>

namespace albinjohansson::tiled {

TiledObject::TiledObject() = default;

TiledObject::~TiledObject() = default;

void TiledObject::AddAttribute(const std::string& id, const std::string& value) {
  attributes.emplace(id, value);
}

void TiledObject::AddProperty(const TiledProperty& property) {
  properties.push_back(property);
}

const std::string& TiledObject::GetAttribute(const std::string& id) const {
  return attributes.at(id);
}

bool TiledObject::HasAttribute(const std::string& id) const {
  return attributes.count(id);
}

const TiledProperty& TiledObject::GetProperty(const std::string& id) const {
  for (const auto& property : properties) {
    if (property.name == id) {
      return property;
    }
  }

  throw std::invalid_argument("Failed to find property " + id);
}

bool TiledObject::HasProperty(const std::string& id) const noexcept {
  for (const auto& property : properties) {
    if (property.name == id) {
      return true;
    }
  }
  return false;
}

const std::vector<TiledProperty>& TiledObject::GetProperties() const noexcept {
  return properties;
}

}
