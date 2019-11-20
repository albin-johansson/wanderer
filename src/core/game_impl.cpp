#include "game_impl.h"
#include "sound_effect.h"
#include "objects.h"
#include "world_impl.h"
#include <fstream>

using namespace wanderer::audio;

namespace wanderer::core {

GameImpl::GameImpl(visuals::ImageGenerator& imageGenerator) {
  soundEngine = SoundEngine::Create();
  LoadSoundEffects();

  // FIXME questionable parameter to player ctor
  player = Player::Create(imageGenerator.Load("resources/img/player2.png"), *this);
  player->SetSpeed(300);

  world = WorldImpl::Create(imageGenerator, player);
}

GameImpl::~GameImpl() = default;

IGame_uptr GameImpl::Create(visuals::ImageGenerator& imageGenerator) {
  return std::make_unique<GameImpl>(imageGenerator);
}

void GameImpl::LoadSoundEffects() {
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

void GameImpl::PlayerHandleInput(const Input& input) {
  player->HandleInput(input, *this);
}

void GameImpl::Update(float delta) {
  world->Tick(*this, delta);
}

void GameImpl::PlaySound(const std::string& name) const {
  soundEngine->Play(name);
}

Vector2 GameImpl::GetPlayerPosition() const noexcept {
  return player->GetPosition();
}

// TODO these getters might need to be changed
int GameImpl::GetLevelWidth() const noexcept {
  return world->GetWidth();
}

int GameImpl::GetLevelHeight() const noexcept {
  return world->GetHeight();
}

void GameImpl::Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) {
  world->Render(renderer, viewport, alpha);
}

float GameImpl::GetPlayerWidth() const noexcept {
  return player->GetWidth();
}

float GameImpl::GetPlayerHeight() const noexcept {
  return player->GetHeight();
}

Vector2 GameImpl::GetPlayerInterpolatedPosition() const noexcept {
  return player->GetInterpolatedPosition();
}

}
