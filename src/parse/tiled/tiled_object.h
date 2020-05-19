#pragma once
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "tiled_property.h"

namespace tiled {

class TiledObject final {
 public:
  TiledObject();

  ~TiledObject();

  void add_attribute(const std::string& id, const std::string& value);

  void add_property(const TiledProperty& property);

  [[nodiscard]] const std::string& get_attribute(const std::string& id) const;

  [[nodiscard]] std::optional<std::string> attribute(
      const std::string& id) const;

  [[nodiscard]] std::optional<std::string> property(
      const std::string& id) const;

  [[nodiscard]] bool has_attribute(const std::string& id) const;

  [[nodiscard]] const TiledProperty& get_property(const std::string& id) const;

  [[nodiscard]] bool has_property(const std::string& id) const noexcept;

  [[nodiscard]] const std::vector<TiledProperty>& get_properties()
      const noexcept;

 private:
  std::map<std::string, std::string> m_attributes;
  std::vector<TiledProperty> m_properties;
};

}  // namespace tiled
