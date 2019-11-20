#include "abstract_menu.h"
#include "objects.h"

using namespace wanderer::visuals;

namespace wanderer::core {

AbstractMenu::AbstractMenu(IMenuStateMachine* parent) {
  this->parent = Objects::RequireNonNull(parent);
}

AbstractMenu::~AbstractMenu() noexcept = default;

void AbstractMenu::Draw(Renderer& renderer, const Viewport& viewport) const {
  auto bounds = viewport.GetBounds();
  renderer.SetColor(0, 0, 0, 0xAA);
  renderer.RenderFillRect(-1.0f, -1.0f, bounds.GetWidth() + 1, bounds.GetHeight() + 1);
}

}
