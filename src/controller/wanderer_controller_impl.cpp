#include "wanderer_controller_impl.h"
#include <SDL.h>
#include <memory>
#include "bad_state_exception.h"
#include "objects.h"
#include "input.h"

using namespace wanderer::core;
using namespace wanderer::visuals;

namespace wanderer::controller {

WandererControllerImpl::WandererControllerImpl(IWandererCore_uptr core) {
  this->core = Objects::RequireNonNull(std::move(core));

  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
    SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
    throw BadStateException();
  }

  SDL_SetHintWithPriority(SDL_HINT_VIDEO_DOUBLE_BUFFER, "1", SDL_HINT_OVERRIDE);
  SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "1", SDL_HINT_OVERRIDE);
//  SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "opengl", SDL_HINT_NORMAL);

  window = std::make_unique<Window>("Wanderer", dm.w, dm.h);
  window->SetFullscreen(true);

  this->core->SetViewportWidth(static_cast<float>(window->GetWidth()));
  this->core->SetViewportHeight(static_cast<float>(window->GetHeight()));

  renderer = std::make_unique<Renderer>(window->GetInternalWindow());
  keyStateManager = std::make_shared<KeyStateManager>();

  auto vsyncDelta = static_cast<float>(dm.refresh_rate);
  fixedTimestepLoop = new SmoothFixedTimestepLoop(keyStateManager, vsyncDelta);
}

WandererControllerImpl::~WandererControllerImpl() {
  delete fixedTimestepLoop;
}

void WandererControllerImpl::Run() {
  running = true;
  window->Show();

  while (running && !fixedTimestepLoop->ShouldQuit()) {
    fixedTimestepLoop->Update(*core, *renderer); // TODO test variable time step loop
  }

  window->Hide();
}

void WandererControllerImpl::Quit() {
  running = false;
}

void WandererControllerImpl::MovePlayer(Direction direction) {
  core->MovePlayer(direction);
}

void WandererControllerImpl::StopPlayer(Direction direction) {
  core->StopPlayer(direction);
}

}