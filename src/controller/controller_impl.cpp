#include "controller_impl.h"
#include "objects.h"
#include <utility>

using namespace wanderer::model;
using namespace wanderer::view;
using namespace centurion::visuals;
using namespace centurion::input;

namespace wanderer::controller {

ControllerImpl::ControllerImpl(IModel_sptr model, IView_uptr view, IWindow_uptr window) {
  this->model = Objects::RequireNonNull(std::move(model));
  this->view = Objects::RequireNonNull(std::move(view));
  this->window = Objects::RequireNonNull(std::move(window));
  inputDispatcher = InputDispatcher::CreateUnique();
}

ControllerImpl::~ControllerImpl() = default;

void ControllerImpl::Run() {
  window->Show();

  bool running = true;
  while (running) {
    inputDispatcher->Update();

    if (inputDispatcher->ReceivedQuit()) {
      running = false;
      continue;
    }

    model->Update(0);

    window->SetColor(Color::GRAY);
    window->RenderClear();
    window->ApplyRendering();

    SDL_Delay(30);
  }

  window->Hide();
}

}