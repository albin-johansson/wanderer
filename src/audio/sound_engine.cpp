#include "sound_engine.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "sound_effect.h"

using namespace centurion;

namespace albinjohansson::wanderer {

SoundEngine::SoundEngine(const std::string& file)
{
  load_sounds(file);
}

SoundEngine::~SoundEngine() = default;

void SoundEngine::load_sounds(const std::string& file)
{
  try {
    std::ifstream infile{file};
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);
      register_sound(id, SoundEffect::unique(path.c_str()));
    }
  } catch (std::exception& e) {
    std::cout << "Failed to load sound effects! Error: " << e.what() << "\n";
  }
}

void SoundEngine::register_sound(const std::string& id,
                                 Unique<SoundEffect> sound)
{
  if (!sound) {
    throw std::invalid_argument{"Null sound!"};
  }
  sounds.emplace(id, std::move(sound));
}

SoundEffect& SoundEngine::get_sound(const std::string& id) const noexcept
{
  return *sounds.at(id);
}

}  // namespace albinjohansson::wanderer
