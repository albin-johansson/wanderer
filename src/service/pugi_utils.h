#pragma once
#include <pugixml.hpp>
#include <string>

namespace wanderer {

class PugiUtils final {
 public:
  PugiUtils() = delete;

  [[nodiscard]] static pugi::xml_document load_document(
      const std::string& path);
};

}  // namespace wanderer
