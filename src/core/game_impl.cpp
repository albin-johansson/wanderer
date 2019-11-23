#include "game_impl.h"
#include "sound_effect.h"
#include "objects.h"
#include "world_impl.h"
#include <fstream>

namespace albinjohansson::wanderer {

GameImpl::GameImpl(ImageGenerator& imageGenerator) {
  soundEngine = SoundEngine::Create();
  LoadSoundEffects();

  world = WorldImpl::Create(imageGenerator);
}

GameImpl::~GameImpl() = default;

IGame_uptr GameImpl::Create(ImageGenerator& imageGenerator) {
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

void GameImpl::Update(float delta) {
  world->Tick(*this, delta);
}

void GameImpl::PlaySound(const std::string& name) const {
  soundEngine->Play(name);
}

}
