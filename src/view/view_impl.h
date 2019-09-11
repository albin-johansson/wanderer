#pragma once
#include "view.h"
#include "model.h"
#include <memory>

namespace wanderer::view {

/**
 * The ViewImpl class is an implementation of the IView interface.
 *
 * \since 0.1.0
 */
class ViewImpl : public IView {
 private:
  std::weak_ptr<wanderer::model::IModel> model;

  /**
   * \param model a weak pointer to the associated IModel instance.
   * \since 0.1.0
   */
  explicit ViewImpl(std::weak_ptr<wanderer::model::IModel> model);

 public:
  ~ViewImpl() override;

  ViewImpl(const ViewImpl& model) = delete;

  ViewImpl& operator=(const ViewImpl& model) = delete;

  /**
   * Creates and returns a unique pointer to an IView instance.
   *
   * \param model a weak pointer to the associated IModel instance.
   * \return a unique pointer to an IView instance.
   * \since 0.1.0
   */
  friend std::unique_ptr<IView> CreateView(std::weak_ptr<wanderer::model::IModel> model);

};

}