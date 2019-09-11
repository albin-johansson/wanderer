#include "controller_impl.h"
#include "objects.h"
#include <utility>

using namespace wanderer::model;
using namespace wanderer::view;
using namespace centurion::visuals;
using namespace centurion::input;

namespace wanderer::controller {

ControllerImpl::ControllerImpl(IModel_sptr model, IView_uptr view) {
  this->model = Objects::RequireNonNull(std::move(model));
  this->view = Objects::RequireNonNull(std::move(view));
  window = Window::CreateUnique(800, 600);
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
    SDL_Delay(30);
  }

  window->Hide();
}

}