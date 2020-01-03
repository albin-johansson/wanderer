#include "sound_engine.h"
#include "sound_effect.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

namespace albinjohansson::wanderer {

SoundEngine::SoundEngine(const std::string& file) {
  LoadSounds(file);
}

SoundEngine::~SoundEngine() = default;

void SoundEngine::LoadSounds(const std::string& file) {
  try {
    std::ifstream infile{file};
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);
      Register(id, std::make_unique<SoundEffect>(path));
    }
  } catch (std::exception& e) {
    std::cout << "Failed to load sound effects! Error: " << e.what() << "\n";
  }
}

void SoundEngine::Register(const std::string& id, std::unique_ptr<SoundEffect> sound) {
  if (!sound) {
    throw std::invalid_argument{"Null sound!"};
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
