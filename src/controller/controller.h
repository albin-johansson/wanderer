#pragma once
#include <memory>

namespace wanderer::controller {

/**
 * \brief The Controller class is an interface that specifies the controller facade for the application.
 *
 * \since 0.1.0
 */
class IController {
 protected:
  IController() = default;

 public:
  virtual ~IController() = default;

  /**
   * Runs the application.
   *
   * \since 0.1.0
   */
  virtual void Run() = 0;

};

using IController_uptr = std::unique_ptr<IController>;

} // namespace wanderer::controller