#pragma once
#include "model_impl.h"
#include <memory>

namespace wanderer::model {

inline std::unique_ptr<IModel> CreateModel() {
  return std::unique_ptr<IModel>(new ModelImpl());
}

}