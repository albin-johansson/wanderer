#pragma once
#include <map>
#include <string>
#include <memory>
#include "sound_effect.h"

namespace wanderer::audio {

class SoundEngine;

using SoundEngine_uptr = std::unique_ptr<SoundEngine>;
using SoundEngine_sptr = std::shared_ptr<SoundEngine>;
using SoundEngine_wptr = std::weak_ptr<SoundEngine>;

class SoundEngine final { // TODO expand
 private:
  std::map<std::string, SoundEffect_uptr> sounds;

 public:
  SoundEngine();

  ~SoundEngine();

  static SoundEngine_uptr Create();

  void Register(std::string id, SoundEffect_uptr sound);

  void Play(const std::string& id);
};

}
