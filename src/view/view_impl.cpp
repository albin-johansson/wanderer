#include "view_impl.h"

#include <utility>
#include "objects.h"

using namespace wanderer::model;

namespace wanderer::view {

ViewImpl::ViewImpl(std::weak_ptr<wanderer::model::IModel> model) {
  this->model = std::move(model);
}

ViewImpl::~ViewImpl() = default;

}