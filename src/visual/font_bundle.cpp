#include "font_bundle.h"

using namespace centurion;

namespace wanderer {

FontBundle::FontBundle(const char* file)
    : m_font12{file, 12},
      m_font18{file, 18},
      m_font24{file, 24},
      m_font36{file, 36}
{}

FontBundle::~FontBundle() = default;

const Font& FontBundle::get_font_12() const noexcept
{
  return m_font12;
}

const Font& FontBundle::get_font_18() const noexcept
{
  return m_font18;
}

const Font& FontBundle::get_font_24() const noexcept
{
  return m_font24;
}

const Font& FontBundle::get_font_36() const noexcept
{
  return m_font36;
}

}  // namespace wanderer
