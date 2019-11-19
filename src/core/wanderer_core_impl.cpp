#include "wanderer_core_impl.h"
#include "menu_state_machine_impl.h"
#include "objects.h"
#include "sound_effect.h"
#include <utility>
#include <fstream>

using namespace wanderer::visuals;
using namespace wanderer::audio;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl(visuals::ImageGenerator_sptr imgGenerator)
    : viewport(Viewport(1, 1, 1, 1)) { // TODO default vp ctor
  imageGenerator = Objects::RequireNonNull(std::move(imgGenerator));

  soundEngine = SoundEngine::Create();
  LoadSoundEffects();

  menuStateMachine = MenuStateMachineImpl::Create(this);

  player = Player::Create(imageGenerator->Load("resources/img/player2.png"));
  player->SetSpeed(300);

  world = World::Create(imageGenerator, player);

  viewport.SetLevelWidth(static_cast<float>(world->GetWidth()));
  viewport.SetLevelHeight(static_cast<float>(world->GetHeight()));
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::LoadSoundEffects() {
  try {
    std::ifstream infile("resources/audio/sfx.txt");
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);
      soundEngine->Register(id, SoundEffect::Create(path));
    }
  } catch (std::exception& e) {
    SDL_Log("Failed to load sound effects! Error: %s", e.what());
  }
}

void WandererCoreImpl::HandleInput(const Input& input) {
  menuStateMachine->HandleInput(input);
  if (!menuStateMachine->IsBlocking()) {
    player->HandleInput(input);
  }
}

void WandererCoreImpl::Update(float delta) {
  if (!menuStateMachine->IsBlocking()) {
    world->Tick(delta);

    auto pos = player->GetInterpolatedPosition();
    viewport.Track(pos.GetX(), pos.GetY(), player->GetWidth(), player->GetHeight(), delta);
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  world->Render(renderer, viewport, alpha);
  menuStateMachine->Draw(renderer, viewport);
}

void WandererCoreImpl::MovePlayer(Direction direction) {
  player->Move(direction);
}

void WandererCoreImpl::StopPlayer(Direction direction) {
  player->Stop(direction);
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