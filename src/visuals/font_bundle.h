#pragma once
#include "font.h"
#include <string>

namespace albinjohansson::wanderer {

class FontBundle final {
 private:
  Font font12;
  Font font18;
  Font font24;
  Font font36;

 public:
  explicit FontBundle(const std::string& file);

  ~FontBundle();

  [[nodiscard]]
  Font& GetFont12() noexcept;

  [[nodiscard]]
  Font& GetFont18() noexcept;

  [[nodiscard]]
  Font& GetFont24() noexcept;

  [[nodiscard]]
  Font& GetFont36() noexcept;

};

}
