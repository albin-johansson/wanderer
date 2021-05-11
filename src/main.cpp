// clang-format off
#define RUNE_TEXTURE_ID_UNDERLYING_TYPE entt::id_type
#define RUNE_GRAPHICS_RENDERER_FLAGS cen::renderer::accelerated | cen::renderer::target_textures
// clang-format on

#include <centurion.hpp>  // library
#include <entt.hpp>       // id_type

#include "wanderer_engine.hpp"

auto main(int, char**) -> int
{
  cen::library centurion;
  wanderer::wanderer_engine engine;
  return engine.run();
}