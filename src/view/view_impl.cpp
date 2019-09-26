#include "view_impl.h"
#include "objects.h"

using namespace wanderer::model;
using namespace centurion::visuals;

namespace wanderer::view {

ViewImpl::ViewImpl(IModel_wptr model, IRenderer_sptr renderer) {
  this->model = std::move(model);
  this->renderer = Objects::RequireNonNull(std::move(renderer));
}

void ViewImpl::Render() noexcept {
  renderer->SetColor(Color::BLACK);
  renderer->RenderClear();

  static int i = 0;

  ++i;
  if (i > 100) {
    i = 0;
  }

  renderer->SetColor(Color::RED);
  renderer->RenderFilledRect(Rectangle(100 + (i * 5), 200, 200, 200));

  renderer->RenderString("Wanderer!", 100, 100);

  renderer->ApplyRendering();
}

void ViewImpl::SetFontBundle(IFontBundle_uptr fontBundle) noexcept {
  this->fontBundle = std::move(fontBundle);
}

ViewImpl::~ViewImpl() = default;

} // namespace wanderer::view