#pragma once
#include "tiled_property.h"
#include <string>
#include <map>
#include <vector>

namespace albinjohansson::tiled {

class TiledObject final {
 private:
  std::map<std::string, std::string> attributes;
  std::vector<TiledProperty> properties;

 public:
  TiledObject();

  ~TiledObject();

  void AddAttribute(const std::string& id, const std::string& value);

  void AddProperty(const TiledProperty& property);

  [[nodiscard]]
  const std::string& GetAttribute(const std::string& id) const;

  [[nodiscard]]
  bool HasAttribute(const std::string& id) const;

  [[nodiscard]]
  const TiledProperty& GetProperty(const std::string& id) const;

  [[nodiscard]]
  bool HasProperty(const std::string& id) const noexcept;

  [[nodiscard]]
  const std::vector<TiledProperty>& GetProperties() const noexcept;
};

}
