#pragma once

#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class Resource final {
 public:
  Resource() = delete;

  static std::string img(CZString name) noexcept;

  static std::string font(CZString name) noexcept;

  static std::string sfx(CZString name) noexcept;

  static std::string map(CZString name) noexcept;

  static std::string menu(CZString name) noexcept;

 private:
  inline static const std::string imagePath = "resources/img/";
  inline static const std::string fontPath = "resources/font/";
  inline static const std::string sfxPath = "resources/audio/";
  inline static const std::string mapPath = "resources/map/";
  inline static const std::string menuPath = "resources/menu/";
};

}  // namespace albinjohansson::wanderer
