#pragma once
#include <utility>
#include "view_impl.h"
#include "model.h"

namespace wanderer::view {

inline IView_uptr CreateView(wanderer::model::IModel_wptr model) {
  return std::unique_ptr<ViewImpl>(new ViewImpl(std::move(model)));
}

}