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

  void add_attribute(const std::string& id, const std::string& value);

  void add_property(const TiledProperty& property);

  [[nodiscard]]
  const std::string& get_attribute(const std::string& id) const;

  [[nodiscard]]
  bool has_attribute(const std::string& id) const;

  [[nodiscard]]
  const TiledProperty& get_property(const std::string& id) const;

  [[nodiscard]]
  bool has_property(const std::string& id) const noexcept;

  [[nodiscard]]
  const std::vector<TiledProperty>& get_properties() const noexcept;
};

}
