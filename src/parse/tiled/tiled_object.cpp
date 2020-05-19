#include "tiled_object.h"

#include <algorithm>
#include <stdexcept>

namespace tiled {

TiledObject::TiledObject() = default;

TiledObject::~TiledObject() = default;

void TiledObject::add_attribute(const std::string& id, const std::string& value)
{
  m_attributes.emplace(id, value);
}

void TiledObject::add_property(const TiledProperty& property)
{
  m_properties.push_back(property);
}

std::optional<std::string> TiledObject::attribute(const std::string& id) const
{
  if (m_attributes.count(id)) {
    return m_attributes.at(id);
  } else {
    return std::nullopt;
  }
}

std::optional<std::string> TiledObject::property(const std::string& id) const
{
  if (has_property(id)) {
    return get_property(id).value;
  } else {
    return std::nullopt;
  }
}

const std::string& TiledObject::get_attribute(const std::string& id) const
{
  return m_attributes.at(id);
}

bool TiledObject::has_attribute(const std::string& id) const
{
  return m_attributes.count(id);
}

const TiledProperty& TiledObject::get_property(const std::string& id) const
{
  const auto res = std::find_if(
      m_properties.begin(),
      m_properties.end(),
      [&id](const auto& property) noexcept { return property.name == id; });
  if (res != m_properties.end()) {
    return *res;
  } else {
    throw std::invalid_argument("Failed to find property " + id);
  }
}

bool TiledObject::has_property(const std::string& id) const noexcept
{
  for (const auto& property : m_properties) {
    if (property.name == id) {
      return true;
    }
  }
  return false;
}

const std::vector<TiledProperty>& TiledObject::get_properties() const noexcept
{
  return m_properties;
}

}  // namespace tiled
