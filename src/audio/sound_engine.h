#pragma once
#include "sound_effect.h"
#include <map>
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

class SoundEngine final { // TODO expand
 private:
  std::map<std::string, std::unique_ptr<SoundEffect>> sounds;
  bool enabled = true;

 public:
  SoundEngine();

  ~SoundEngine();

  void Register(std::string id, std::unique_ptr<SoundEffect> sound);

  void Play(const std::string& id);

  void SetEnabled(bool enabled) noexcept;

  [[nodiscard]] bool IsEnabled() const noexcept;
};

}
