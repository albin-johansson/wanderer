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
  renderer->SetColor(Color::WHITE);
  renderer->RenderClear();

  IModel_sptr tmpModel = model.lock();
  if (tmpModel != nullptr) {
    Player_sptr player = tmpModel->GetPlayer();

    Rectangle rect(player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight());

    renderer->SetColor(Color::RED);
    renderer->RenderFilledRect(rect);
  }

  renderer->ApplyRendering();
}

ViewImpl::~ViewImpl() = default;

} // namespace wanderer::view