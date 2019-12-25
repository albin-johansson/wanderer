#include "abstract_menu.h"
#include "require.h"
;

namespace albinjohansson::wanderer {

AbstractMenu::AbstractMenu(IMenuStateMachine* parent) {
  this->parent = Require::NotNull(parent);
}

AbstractMenu::~AbstractMenu() noexcept = default;

void AbstractMenu::Draw(Renderer& renderer, const Viewport& viewport, FontBundle& fonts) const {
  auto bounds = viewport.GetBounds();
  renderer.SetColor(0, 0, 0, 0xAA);
  renderer.RenderFillRect(-1.0f, -1.0f, bounds.GetWidth() + 1, bounds.GetHeight() + 1);
}

}
