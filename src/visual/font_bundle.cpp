#include "font_bundle.h"

using namespace centurion;

namespace albinjohansson::wanderer {

FontBundle::FontBundle(const char* file)
    : font12{file, 12}, font18{file, 18}, font24{file, 24}, font36{file, 36}
{}

FontBundle::~FontBundle() = default;

const Font& FontBundle::get_font_12() const noexcept
{
  return font12;
}

const Font& FontBundle::get_font_18() const noexcept
{
  return font18;
}

const Font& FontBundle::get_font_24() const noexcept
{
  return font24;
}

const Font& FontBundle::get_font_36() const noexcept
{
  return font36;
}

}  // namespace albinjohansson::wanderer
