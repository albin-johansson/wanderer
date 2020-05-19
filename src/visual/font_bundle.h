#pragma once
#include <font.h>

#include <string>

#include "wanderer_stdinc.h"

namespace wanderer {

class [[deprecated]] FontBundle final
{
 public:
  explicit FontBundle(const char* file);

  ~FontBundle();

  [[nodiscard]] const ctn::Font& get_font_12() const noexcept;

  [[nodiscard]] const ctn::Font& get_font_18() const noexcept;

  [[nodiscard]] const ctn::Font& get_font_24() const noexcept;

  [[nodiscard]] const ctn::Font& get_font_36() const noexcept;

 private:
  ctn::Font m_font12;
  ctn::Font m_font18;
  ctn::Font m_font24;
  ctn::Font m_font36;
};

}  // namespace wanderer
