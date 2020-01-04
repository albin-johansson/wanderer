#pragma once
#include "font.h"
#include <string>

namespace albinjohansson::wanderer {

class FontBundle final {
 private:
  centurion::Font font12;
  centurion::Font font18;
  centurion::Font font24;
  centurion::Font font36;

 public:
  explicit FontBundle(const std::string& file);

  ~FontBundle();

  [[nodiscard]]
  const centurion::Font& get_font_12() const noexcept;

  [[nodiscard]]
  const centurion::Font& get_font_18() const noexcept;

  [[nodiscard]]
  const centurion::Font& get_font_24() const noexcept;

  [[nodiscard]]
  const centurion::Font& get_font_36() const noexcept;

};

}
