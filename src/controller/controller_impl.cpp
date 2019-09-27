#include "controller_impl.h"
#include "objects.h"
#include "input_handler.h"
#include "delta_time_handler.h"
#include <utility>

using namespace wanderer::model;
using namespace wanderer::view;
using namespace wanderer::util;
using namespace centurion::visuals;
using namespace centurion::input;

namespace wanderer::controller {

ControllerImpl::ControllerImpl(IModel_sptr model, IView_uptr view, IWindow_uptr window) {
  this->model = Objects::RequireNonNull(std::move(model));
  this->view = Objects::RequireNonNull(std::move(view));
  this->window = Objects::RequireNonNull(std::move(window));
  inputDispatcher = InputDispatcher::CreateUnique();

  auto inputHandler = std::make_shared<InputHandler>(this);
  inputDispatcher->AddKeyListener(inputHandler);
  inputDispatcher->AddMouseListener(inputHandler);

  InitFonts();
}

void ControllerImpl::InitFonts() {
  Font_sptr typeWriterFont = Font::CreateShared("resources/type_writer.ttf", 16);
  window->SetFont(typeWriterFont);
}

ControllerImpl::~ControllerImpl() = default;

void ControllerImpl::Run() {
  window->Show();
  running = true;

  DeltaTimeHandler deltaTimeHandler;

  while (running) {
    deltaTimeHandler.BeginIteration();

    inputDispatcher->Update();
    if (inputDispatcher->ReceivedQuit()) {
      running = false;
      continue;
    }

    model->Update(deltaTimeHandler.GetDelta());

    if (deltaTimeHandler.GetSkips() == 0) {
      view->Render();
    } else {
      deltaTimeHandler.DecreaseSkips();
    }

    deltaTimeHandler.EndIteration();
  }
  window->Hide();
}

void ControllerImpl::Exit() {
  running = false;
}

} // namespace wanderer::controller