#pragma once
#include "view.h"
#include "model.h"
#include <memory>
#include <ctn_renderer_interface.h>
#include <ctn_color.h>

using namespace centurion::visuals;
using namespace centurion::geo;

namespace wanderer::view {

/**
 * The ViewImpl class is an implementation of the IView interface.
 *
 * @since 0.1.0
 */
class ViewImpl : public IView {
 private:
  centurion::visuals::IRenderer_sptr renderer = nullptr;
  model::IModel_wptr model;

  /**
   * @param model a weak pointer to the associated IModel instance.
   * @param renderer a shared pointer to the associated IRenderer instance.
   * @throws invalid_argument if the supplied renderer pointer is null.
   * @since 0.1.0
   */
  explicit ViewImpl(model::IModel_wptr model,
                    centurion::visuals::IRenderer_sptr renderer);

 public:
  ~ViewImpl() override;

  ViewImpl(const ViewImpl& model) = delete;

  ViewImpl& operator=(const ViewImpl& model) = delete;

  /**
   * Creates and returns a unique pointer to an IView instance.
   *
   * @param model a weak pointer to the associated IModel instance.
   * @param renderer a shared pointer to the assoicated IRenderer instance.
   * @return a unique pointer to an IView instance.
   * @throws invalid_argument if the supplied renderer pointer is null.
   * @since 0.1.0
   */
  friend IView_uptr CreateView(model::IModel_wptr model,
                               centurion::visuals::IRenderer_sptr renderer);

  /**
   * Renders everything.
   *
   * @since 0.1.0
   */
  void Render() noexcept override;
};

} // namespace wanderer::view