#include "sound_engine.h"
#include <stdexcept>

namespace wanderer::audio {

SoundEngine::SoundEngine() {

}

SoundEngine::~SoundEngine() = default;

SoundEngine_uptr SoundEngine::Create() {
  return std::make_unique<SoundEngine>();
}

void SoundEngine::Register(std::string id, SoundEffect_uptr sound) {
  if (sound == nullptr) {
    throw std::invalid_argument("Null sound!");
  }
  sounds.insert(std::pair<std::string, SoundEffect_uptr>(id, std::move(sound)));
}

void SoundEngine::Play(const std::string& id) {
  sounds.at(id)->Play();
}

}
