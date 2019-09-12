#pragma once
#include "model.h"
#include <memory>
#include <ctn_renderer_interface.h>

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

  /**
   * Clears the entire rendering area.
   *
   * \since 0.1.0
   */
  virtual void ClearCanvas() = 0;

  /**
   * Applies the previous rendering operations.
   *
   * \since 0.1.0
   */
  virtual void ApplyRendering() = 0;

};

using IView_uptr = std::unique_ptr<IView>;

} // namespace wanderer::view