#include <centurion_everything.h>
#include "model.h"
#include "model_factory.h"
#include "controller.h"
#include "controller_factory.h"
#include "view.h"
#include "view_factory.h"

/**
 * Initializes the model, view and controller and runs the application.
 *
 * \since 0.1.0
 */
static void Run() {
  using namespace wanderer::model;
  using namespace wanderer::view;
  using namespace wanderer::controller;

  std::shared_ptr<IModel> model = CreateModel();
  std::unique_ptr<IView> view = CreateView(model);
  std::unique_ptr<IController> controller = CreateController(model, std::move(view));
  controller->Run();
}

int main(int argc, char** argv) {
  using namespace centurion;
  Centurion::Init();
  Run();
  Centurion::Close();
  return 0;
}