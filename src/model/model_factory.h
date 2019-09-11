#pragma once
#include "model_impl.h"
#include <memory>

namespace wanderer::model {

inline IModel_uptr CreateModel() {
  return std::unique_ptr<IModel>(new ModelImpl());
}

}