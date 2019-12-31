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
  const Font& GetFont12() const noexcept;

  [[nodiscard]]
  const Font& GetFont18() const noexcept;

  [[nodiscard]]
  const Font& GetFont24() const noexcept;

  [[nodiscard]]
  const Font& GetFont36() const noexcept;

};

}
