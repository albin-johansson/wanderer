#pragma once
#include <memory>
#include <utility>
#include "controller_impl.h"
#include "controller.h"
#include "model.h"
#include "view.h"

namespace wanderer::controller {

inline std::unique_ptr<IController> CreateController(std::shared_ptr<wanderer::model::IModel> model,
                                                     std::unique_ptr<wanderer::view::IView> view) {
  auto controllerPtr = new ControllerImpl(std::move(model), std::move(view));
  return std::unique_ptr<ControllerImpl>(controllerPtr);
}

}