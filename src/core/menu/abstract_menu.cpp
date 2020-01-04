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
  renderer.SetColor(0, 0, 0, 0xAA);
  renderer.RenderFillRect(-1.0f, -1.0f, bounds.GetWidth() + 1, bounds.GetHeight() + 1);
}

}
