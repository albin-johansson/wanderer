#pragma once
#include <utility>
#include "view_impl.h"
#include "model.h"

namespace wanderer::view {

std::unique_ptr<IView> CreateView(std::weak_ptr<wanderer::model::IModel> model) {
  return std::unique_ptr<ViewImpl>(new ViewImpl(std::move(model)));
}

}