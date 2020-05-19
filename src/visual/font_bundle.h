#pragma once
#include <font.h>

#include <string>

#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class [[deprecated]] FontBundle final
{
 private:
  ctn::Font font12;
  ctn::Font font18;
  ctn::Font font24;
  ctn::Font font36;

 public:
  explicit FontBundle(const char* file);

  ~FontBundle();

  [[nodiscard]] const ctn::Font& get_font_12() const noexcept;

  [[nodiscard]] const ctn::Font& get_font_18() const noexcept;

  [[nodiscard]] const ctn::Font& get_font_24() const noexcept;

  [[nodiscard]] const ctn::Font& get_font_36() const noexcept;
};

}  // namespace albinjohansson::wanderer
