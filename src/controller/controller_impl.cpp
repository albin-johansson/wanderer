#include "controller_impl.h"
#include "objects.h"
#include <utility>
#include <iostream>

using namespace wanderer::model;
using namespace wanderer::view;

namespace wanderer::controller {

ControllerImpl::ControllerImpl(std::shared_ptr<IModel> model, std::unique_ptr<IView> view) {
  this->model = Objects::RequireNonNull(std::move(model));
  this->view = Objects::RequireNonNull(std::move(view));
}

ControllerImpl::~ControllerImpl() = default;

void ControllerImpl::Run() {
  std::cout << "Running...\n";
}

}