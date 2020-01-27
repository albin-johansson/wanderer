#include "abstract_menu.h"
#include "require.h"
#include "renderer.h"

using namespace centurion;

namespace albinjohansson::wanderer {

AbstractMenu::AbstractMenu(IMenuStateMachine* parent) {
  this->parent = Require::not_null(parent);
}

AbstractMenu::~AbstractMenu() noexcept = default;

void AbstractMenu::draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle&) const {
  const auto& bounds = viewport.get_bounds();
  renderer.set_color(0, 0, 0, 0xAA);
  renderer.fill_rect(-1.0f, -1.0f, bounds.get_width() + 1, bounds.get_height() + 1);
}

}
