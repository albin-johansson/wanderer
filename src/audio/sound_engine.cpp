#include "sound_engine.h"
#include "sound_effect.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

namespace albinjohansson::wanderer {

SoundEngine::SoundEngine(const std::string& file) {
  load_sounds(file);
}

SoundEngine::~SoundEngine() = default;

void SoundEngine::load_sounds(const std::string& file) {
  try {
    std::ifstream infile{file};
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);
      registerSound(id, std::make_unique<SoundEffect>(path));
    }
  } catch (std::exception& e) {
    std::cout << "Failed to load sound effects! Error: " << e.what() << "\n";
  }
}

void SoundEngine::registerSound(const std::string& id, std::unique_ptr<SoundEffect> sound) {
  if (!sound) {
    throw std::invalid_argument{"Null sound!"};
  }
  sounds.emplace(id, std::move(sound));
}

void SoundEngine::play(const std::string& id) {
  if (enabled) {
    sounds.at(id)->play();
  }
}

void SoundEngine::set_enabled(bool enabled) noexcept {
  this->enabled = enabled;
}

bool SoundEngine::is_enabled() const noexcept {
  return enabled;
}

}
