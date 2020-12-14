#include "graphics_context.hpp"

#include "make_renderer.hpp"

namespace wanderer {

graphics_context::graphics_context(const cen::window& window)
    : m_renderer{make_renderer(window)}
{}

}  // namespace wanderer
