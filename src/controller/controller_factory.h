#pragma once
#include <memory>
#include <utility>
#include "controller_impl.h"
#include "controller.h"
#include "model.h"
#include "view.h"

namespace wanderer::controller {

inline IController_uptr CreateController(wanderer::model::IModel_sptr model,
                                         wanderer::view::IView_uptr view) {
  auto controllerPtr = new ControllerImpl(std::move(model), std::move(view));
  return std::unique_ptr<ControllerImpl>(controllerPtr);
}

}