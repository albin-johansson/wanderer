#include "abstract_menu.h"

#include "renderer.h"
#include "require.h"

using namespace centurion;
using namespace centurion::video;

namespace albinjohansson::wanderer {

AbstractMenu::AbstractMenu(IMenuStateMachine* parent)
{
  this->parent = Require::not_null(parent);
}

AbstractMenu::~AbstractMenu() noexcept = default;

void AbstractMenu::draw(Renderer& renderer,
                        const Viewport& viewport,
                        const FontBundle&) const
{
  const auto& bounds = viewport.get_bounds();
  renderer.set_color({0, 0, 0, 0xAA});
  renderer.fill_rect_f(
      {-1.0f, -1.0f, bounds.get_width() + 1, bounds.get_height() + 1});
}

}  // namespace albinjohansson::wanderer
