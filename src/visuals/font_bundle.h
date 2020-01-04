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
  const centurion::Font& GetFont12() const noexcept;

  [[nodiscard]]
  const centurion::Font& GetFont18() const noexcept;

  [[nodiscard]]
  const centurion::Font& GetFont24() const noexcept;

  [[nodiscard]]
  const centurion::Font& GetFont36() const noexcept;

};

}
