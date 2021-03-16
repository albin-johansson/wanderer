#include "graphics_context.hpp"

#include "make_renderer.hpp"

namespace wanderer {

graphics_context::graphics_context(const cen::window& window)
    : m_renderer{make_renderer(window)}
{
  m_textures.reserve(10);
}

void graphics_context::render(const texture_index index,
                              const cen::irect& src,
                              const cen::frect& dst) noexcept
{
  const auto& texture = find(index);
  m_renderer.render_t(texture, src, dst);
}

auto graphics_context::load(const texture_id id, const std::string& path)
    -> texture_index
{
  if (const auto it = m_identifiers.find(id); it != m_identifiers.end()) {
    return it->second;
  }

  const auto index = m_textures.size();

  m_textures.emplace_back(m_renderer, path);
  m_identifiers.try_emplace(id, index);

  return texture_index{index};
}

auto graphics_context::to_index(const texture_id id) const -> texture_index
{
  return m_identifiers.at(id);
}

auto graphics_context::find(const texture_index index) const noexcept
    -> const cen::texture&
{
  if (index >= m_textures.size()) {
    int i = 1;
  }

  assert(index < m_textures.size());
  return m_textures[index];
}

}  // namespace wanderer
