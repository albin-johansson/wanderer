#include "resources.hpp"

using namespace std::string_literals;

namespace wanderer::resources {

auto texture(cen::czstring resource) -> std::string
{
  return "resources/images/"s + resource;
}

auto font(cen::czstring resource) -> std::string
{
  return "resources/fonts/"s + resource;
}

auto sound(cen::czstring resource) -> std::string
{
  return "resources/audio/"s + resource;
}

auto map(cen::czstring resource) -> std::string
{
  return "resources/maps"s + resource;
}

}  // namespace wanderer::resources
