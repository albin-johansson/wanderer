#include "graphics_context.hpp"

#include "make_renderer.hpp"
#include "texture_loader.hpp"

namespace wanderer {

graphics_context::graphics_context(const cen::window& window)
    : m_renderer{make_renderer(window)}
{}

auto graphics_context::load_texture(const entt::id_type id, cen::czstring path)
    -> texture_handle
{
  return m_textures.load<texture_loader>(id, m_renderer, path);
}

auto graphics_context::get_texture(const entt::id_type id) const
    -> texture_handle
{
  return m_textures.handle(id);
}

}  // namespace wanderer
