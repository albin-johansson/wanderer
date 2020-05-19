#pragma once
#include <sound_effect.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class SoundEngine final {
 private:
  std::unordered_map<std::string, UniquePtr<centurion::SoundEffect>> sounds;

  void load_sounds(const std::string& file);

  void register_sound(const std::string& id,
                      UniquePtr<centurion::SoundEffect> sound);

 public:
  explicit SoundEngine(const std::string& file);

  ~SoundEngine();

  [[nodiscard]] centurion::SoundEffect& get_sound(
      const std::string& id) const noexcept;
};

}  // namespace albinjohansson::wanderer
