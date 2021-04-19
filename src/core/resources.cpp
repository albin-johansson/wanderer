#include "resources.hpp"

using namespace std::string_literals;

namespace wanderer::resources {

auto texture(const czstring resource) -> std::string
{
  static const auto dir = "resources/images/"s;
  return dir + resource;
}

auto font(const czstring resource) -> std::string
{
  static const auto dir = "resources/fonts/"s;
  return dir + resource;
}

auto sound(const czstring resource) -> std::string
{
  static const auto dir = "resources/audio/"s;
  return dir + resource;
}

auto map(const czstring resource) -> std::string
{
  static const auto dir = "resources/maps/"s;
  return dir + resource;
}

}  // namespace wanderer::resources
