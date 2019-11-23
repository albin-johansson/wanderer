#pragma once
#include "font.h"
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

class FontBundle;

using FontBundle_uptr = std::unique_ptr<FontBundle>;
using FontBundle_sptr = std::shared_ptr<FontBundle>;
using FontBundle_wptr = std::weak_ptr<FontBundle>;

class FontBundle final {
 private:
  Font font12;
  Font font18;
  Font font24;
  Font font36;

 public:
  explicit FontBundle(const std::string& file);

  ~FontBundle();

  [[nodiscard]] static FontBundle_uptr Create(const std::string& file);

  [[nodiscard]] Font& GetFont12() noexcept { return font12; }

  [[nodiscard]] Font& GetFont18() noexcept { return font18; }

  [[nodiscard]] Font& GetFont24() noexcept { return font24; }

  [[nodiscard]] Font& GetFont36() noexcept { return font36; }

};

}
