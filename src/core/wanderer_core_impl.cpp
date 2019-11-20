#include "wanderer_core_impl.h"
#include "menu_state_machine_impl.h"
#include "objects.h"
#include "game_impl.h"

using namespace wanderer::visuals;
using namespace wanderer::audio;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl(visuals::ImageGenerator_sptr imageGenerator)
    : viewport(Viewport(1, 1, 1, 1)) { // TODO default vp ctor
  Objects::RequireNonNull(imageGenerator);

  menuStateMachine = MenuStateMachineImpl::Create(this); // TODO fix "this" parameter

  game = GameImpl::Create(*imageGenerator);

  viewport.SetLevelWidth(static_cast<float>(game->GetLevelWidth()));
  viewport.SetLevelHeight(static_cast<float>(game->GetLevelHeight()));
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::HandleInput(const Input& input) {
  menuStateMachine->HandleInput(input);
  if (!menuStateMachine->IsBlocking()) {
    game->PlayerHandleInput(input);
  }
}

void WandererCoreImpl::Update(float delta) {
  if (!menuStateMachine->IsBlocking()) {
    game->Update(delta);

    auto pos = game->GetPlayerInterpolatedPosition();
    viewport.Track(pos.GetX(), pos.GetY(),
                   game->GetPlayerWidth(),
                   game->GetPlayerHeight(),
                   delta);
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  game->Render(renderer, viewport, alpha);
  menuStateMachine->Draw(renderer, viewport);
}

void WandererCoreImpl::SetViewportWidth(float width) {
  viewport.SetWidth(width);
}

void WandererCoreImpl::SetViewportHeight(float height) {
  viewport.SetHeight(height);
}

void WandererCoreImpl::Quit() noexcept {
  shouldQuit = true;
}

}