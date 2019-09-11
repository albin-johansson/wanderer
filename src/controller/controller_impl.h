#pragma once
#include "controller.h"
#include "model.h"
#include "view.h"
#include <memory>

namespace wanderer::controller {

/**
 * The ControllerImpl class is an implementation of the IController interface.
 *
 * \since 0.1.0
 */
class ControllerImpl final : public IController {
 private:
  std::shared_ptr<wanderer::model::IModel> model;
  std::unique_ptr<wanderer::view::IView> view;

  /**
   * \param model a shared pointer to the associated model instance.
   * \param view a unique pointer to the associated view instance.
   * \throws invalid_argument if any of the supplied arguments are nullptr.
   * \since 0.1.0
   */
  ControllerImpl(std::shared_ptr<wanderer::model::IModel> model,
                 std::unique_ptr<wanderer::view::IView> view);

 public:
  ~ControllerImpl() override;

  ControllerImpl(const ControllerImpl& model) = delete;

  ControllerImpl& operator=(const ControllerImpl& model) = delete;

  /**
   * Creates and returns a unique pointer to an IController instance.
   *
   * \param model a shared pointer to the associated IModel instance, may not be nullptr.
   * \param view a unique pointer to the associated IView instance, may not be nullptr.
   * \return a unique pointer to an IController instance.
   * \throws invalid_argument if any of the supplied arguments are nullptr.
   * \since 0.1.0
   */
  friend std::unique_ptr<IController> CreateController(std::shared_ptr<wanderer::model::IModel> model,
                                                       std::unique_ptr<wanderer::view::IView> view);

  void Run() override;

};

}