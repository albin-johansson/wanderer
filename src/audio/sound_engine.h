#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <sound_effect.h>
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class SoundEngine final {
 private:
  std::unordered_map<std::string, unique<centurion::SoundEffect>> sounds;

  void load_sounds(const std::string& file);

  void register_sound(const std::string& id, unique<centurion::SoundEffect> sound);

 public:
  explicit SoundEngine(const std::string& file);

  ~SoundEngine();

  [[nodiscard]]
  centurion::SoundEffect& get_sound(const std::string& id) const noexcept;
};

}
