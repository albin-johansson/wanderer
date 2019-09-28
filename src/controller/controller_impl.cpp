#include "controller_impl.h"
#include "objects.h"
#include "input_handler.h"
#include "delta_time_handler.h"
#include <iostream>

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

  auto targetIterationTime = static_cast<int>(1000.0 / 144.0);
  DeltaTimeHandler deltaTimeHandler(targetIterationTime);

  while (running) {
    deltaTimeHandler.BeginIteration();

    inputDispatcher->Update();
    if (inputDispatcher->ReceivedQuit()) {
      running = false;
      continue;
    }

    auto delta = deltaTimeHandler.GetDelta() * 20;

    model->Update(delta);

    if (deltaTimeHandler.GetSkips() == 0) {
      view->Render();
    } else {
      deltaTimeHandler.DecrementSkips();
    }

    deltaTimeHandler.EndIteration();
  }
  window->Hide();
}

void ControllerImpl::Exit() {
  running = false;
}

void ControllerImpl::MovePlayer(Direction direction) {
  model->MovePlayer(direction);
}

void ControllerImpl::StopPlayer(Direction direction) {
  model->StopPlayer(direction);
}

} // namespace wanderer::controller