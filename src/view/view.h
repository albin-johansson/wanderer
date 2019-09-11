#pragma once
#include "model.h"
#include <memory>

namespace wanderer::view {

/**
 * The IView class is an interface that specifies the view component facade for the application.
 *
 * \since 0.1.0
 */
class IView {
 protected:
  IView() = default;

 public:
  virtual ~IView() = default;

};

using IView_uptr = std::unique_ptr<IView>;

}