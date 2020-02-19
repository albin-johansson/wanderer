#pragma once
#include <font.h>

#include <string>

namespace albinjohansson::wanderer {

class FontBundle final {
 private:
  centurion::video::Font font12;
  centurion::video::Font font18;
  centurion::video::Font font24;
  centurion::video::Font font36;

 public:
  explicit FontBundle(const std::string& file);

  ~FontBundle();

  [[nodiscard]] const centurion::video::Font& get_font_12() const noexcept;

  [[nodiscard]] const centurion::video::Font& get_font_18() const noexcept;

  [[nodiscard]] const centurion::video::Font& get_font_24() const noexcept;

  [[nodiscard]] const centurion::video::Font& get_font_36() const noexcept;
};

}  // namespace albinjohansson::wanderer
