#include "view_impl.h"
#include <utility>

using namespace wanderer::model;

namespace wanderer::view {

ViewImpl::ViewImpl(IModel_wptr model) {
  this->model = std::move(model);
}

ViewImpl::~ViewImpl() = default;

}