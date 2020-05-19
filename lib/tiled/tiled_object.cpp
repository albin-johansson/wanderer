#include "tiled_object.h"
#include <algorithm>
#include <stdexcept>

namespace tiled {

TiledObject::TiledObject() = default;

TiledObject::~TiledObject() = default;

void TiledObject::add_attribute(const std::string& id, const std::string& value) {
  attributes.emplace(id, value);
}

void TiledObject::add_property(const TiledProperty& property) {
  properties.push_back(property);
}

std::optional<std::string> TiledObject::attribute(const std::string& id) const {
  if (attributes.count(id)) {
    return attributes.at(id);
  } else {
    return std::nullopt;
  }
}

std::optional<std::string> TiledObject::property(const std::string& id) const {
  if (has_property(id)) {
    return get_property(id).value;
  } else {
    return std::nullopt;
  }
}

const std::string& TiledObject::get_attribute(const std::string& id) const {
  return attributes.at(id);
}

bool TiledObject::has_attribute(const std::string& id) const {
  return attributes.count(id);
}

const TiledProperty& TiledObject::get_property(const std::string& id) const {
  const auto res = std::find_if(properties.begin(),
                                properties.end(),
                                [&id](const auto& property) noexcept {
                                  return property.name == id;
                                });
  if (res != properties.end()) {
    return *res;
  } else {
    throw std::invalid_argument("Failed to find property " + id);
  }
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
