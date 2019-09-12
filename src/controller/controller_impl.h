#pragma once
#include "controller.h"
#include "model.h"
#include "view.h"
#include <memory>
#include <ctn_window_interface.h>
#include <ctn_input_dispatcher.h>

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
   * \param window a unique pointer to the associated parent window instance.
   * \throws invalid_argument if any of the supplied arguments are nullptr.
   * \since 0.1.0
   */
  ControllerImpl(wanderer::model::IModel_sptr model,
                 wanderer::view::IView_uptr view,
                 centurion::visuals::IWindow_uptr window);

 public:
  ~ControllerImpl() override;

  ControllerImpl(const ControllerImpl& model) = delete;

  ControllerImpl& operator=(const ControllerImpl& model) = delete;

  /**
   * Creates and returns a unique pointer to an IController instance.
   *
   * \param model a shared pointer to the associated IModel instance, may not be nullptr.
   * \param view a unique pointer to the associated IView instance, may not be nullptr.
   * \param window a unique pointer to the associated parent window instance.
   * \return a unique pointer to an IController instance.
   * \throws invalid_argument if any of the supplied arguments are nullptr.
   * \since 0.1.0
   */
  friend IController_uptr CreateController(wanderer::model::IModel_sptr model,
                                           wanderer::view::IView_uptr view,
                                           centurion::visuals::IWindow_uptr window);

  void Run() override;

};

} // namespace wanderer::controller