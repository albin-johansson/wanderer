#pragma once
#include <memory>
#include <utility>
#include "controller_impl.h"
#include "controller.h"
#include "model.h"
#include "view.h"

namespace wanderer::controller {

inline IController_uptr CreateController(model::IModel_sptr model,
                                         view::IView_uptr view,
                                         centurion::visuals::IWindow_uptr window) {
  auto controllerPtr = new ControllerImpl(std::move(model), std::move(view), std::move(window));
  return std::unique_ptr<ControllerImpl>(controllerPtr);
}

} // namespace wanderer::controller