#include "tiled_object.h"

namespace albinjohansson::tiled {

TiledObject::TiledObject() = default;

TiledObject::~TiledObject() = default;

void TiledObject::AddProperty(const std::string& id, const std::string& value) {
  attributes.insert(std::pair<std::string, std::string>(id, value));
}

const std::string& TiledObject::GetAttribute(const std::string& id) const {
  return attributes.at(id);
}

bool TiledObject::HasAttribute(const std::string& id) const {
  return attributes.count(id);
}

}
