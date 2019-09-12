#include "model_impl.h"

namespace wanderer::model {

ModelImpl::ModelImpl() {
  world = std::make_unique<World>();
}

void ModelImpl::Update(double delta) {
  world->Update(delta);
}

} // namespace wanderer::model