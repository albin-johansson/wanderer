#include "resource.h"

namespace wanderer {

std::string Resource::img(CZString name) noexcept
{
  return imagePath + (name ? name : "");
}

std::string Resource::font(CZString name) noexcept
{
  return fontPath + (name ? name : "");
}

std::string Resource::sfx(CZString name) noexcept
{
  return sfxPath + (name ? name : "");
}

std::string Resource::map(CZString name) noexcept
{
  return mapPath + (name ? name : "");
}

std::string Resource::menu(CZString name) noexcept
{
  return menuPath + (name ? name : "");
}

}  // namespace wanderer