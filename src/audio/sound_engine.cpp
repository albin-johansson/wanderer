#include "sound_engine.h"
#include "sound_effect.h"
#include <stdexcept>

namespace albinjohansson::wanderer {

SoundEngine::SoundEngine() = default;

SoundEngine::~SoundEngine() = default;

void SoundEngine::Register(std::string id, std::unique_ptr<SoundEffect> sound) {
  if (sound == nullptr) {
    throw std::invalid_argument("Null sound!");
  }
  sounds.emplace(id, std::move(sound));
}

void SoundEngine::Play(const std::string& id) {
  if (enabled) {
    sounds.at(id)->Play();
  }
}

void SoundEngine::SetEnabled(bool enabled) noexcept {
  this->enabled = enabled;
}

bool SoundEngine::IsEnabled() const noexcept {
  return enabled;
}

}
