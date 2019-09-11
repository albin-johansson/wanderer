#pragma once
#include "controller.h"
#include "model.h"
#include "view.h"
#include <memory>
#include <centurion_visuals.h>
#include <centurion_input.h>

namespace wanderer::controller {

/**
 * The ControllerImpl class is an implementation of the IController interface.
 *
 * \since 0.1.0
 */
class ControllerImpl final : public IController {
 private:
  wanderer::model::IModel_sptr model;
  wanderer::view::IView_uptr view;
  centurion::input::InputDispatcher_uptr inputDispatcher;
  centurion::visuals::IWindow_uptr window;

  /**
   * \param model a shared pointer to the associated model instance.
   * \param view a unique pointer to the associated view instance.
   * \throws invalid_argument if any of the supplied arguments are nullptr.
   * \since 0.1.0
   */
  ControllerImpl(wanderer::model::IModel_sptr model, wanderer::view::IView_uptr view);

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
  friend std::unique_ptr<IController> CreateController(wanderer::model::IModel_sptr model,
                                                       wanderer::view::IView_uptr view);

  void Run() override;

};

}