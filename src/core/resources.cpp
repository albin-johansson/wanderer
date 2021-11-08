#include "resources.hpp"

using namespace std::string_literals;

namespace wanderer {

auto GetTextureResource(const CStr resource) -> std::string
{
  static const auto dir = "resources/images/"s;
  return dir + resource;
}

auto GetFontResource(const CStr resource) -> std::string
{
  static const auto dir = "resources/fonts/"s;
  return dir + resource;
}

auto GetSoundResource(const CStr resource) -> std::string
{
  static const auto dir = "resources/audio/"s;
  return dir + resource;
}

auto GetMapResource(const CStr resource) -> std::string
{
  static const auto dir = "resources/maps/"s;
  return dir + resource;
}

}  // namespace wanderer::resources
