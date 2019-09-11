#include <ctn_centurion.h>
#include <centurion_visuals.h>
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
  using namespace centurion::visuals;
  using namespace std;

  auto window = Window::CreateUnique(800, 600);

  IModel_sptr model = CreateModel();
  IView_uptr view = CreateView(model, window->GetRenderer());
  IController_uptr controller = CreateController(model, std::move(view), std::move(window));
  controller->Run();
}

int main(int argc, char** argv) {
  using namespace centurion;
  Centurion::Init();
  Run();
  Centurion::Close();
  return 0;
}