#pragma once
#include "view.h"
#include "model.h"
#include <memory>
#include <ctn_renderer_interface.h>
#include <ctn_color.h>

namespace wanderer::view {

/**
 * The ViewImpl class is an implementation of the IView interface.
 *
 * @since 0.1.0
 */
class ViewImpl : public IView {
 private:
  wanderer::model::IModel_wptr model;
  centurion::visuals::IRenderer_sptr renderer;

  /**
   * @param model a weak pointer to the associated IModel instance.
   * @param renderer a shared pointer to the associated IRenderer instance.
   * @throws invalid_argument if the supplied renderer pointer is null.
   * @since 0.1.0
   */
  explicit ViewImpl(wanderer::model::IModel_wptr model,
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
   * \return a unique pointer to an IView instance.
   * @throws invalid_argument if the supplied renderer pointer is null.
   * @since 0.1.0
   */
  friend IView_uptr CreateView(wanderer::model::IModel_wptr model,
                               centurion::visuals::IRenderer_sptr renderer);

  inline void ClearCanvas() noexcept override {
    renderer->SetColor(centurion::visuals::Color::BLACK);
    renderer->RenderClear();
  }

  inline void ApplyRendering() noexcept override {
    renderer->ApplyRendering();
  };

};

} // namespace wanderer::view