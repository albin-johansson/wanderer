#include "view_impl.h"
#include "objects.h"

using namespace wanderer::model;
using namespace centurion::visuals;

namespace wanderer::view {

ViewImpl::ViewImpl(IModel_wptr model, IRenderer_sptr renderer) {
  this->model = std::move(model);
  this->renderer = Objects::RequireNonNull(std::move(renderer));
}

ViewImpl::~ViewImpl() = default;

} // namespace wanderer::view