#pragma once

#include <unordered_map>

#include "sound_id.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class SoundEngine final {
  friend class SoundEngineParser;

 public:
  ~SoundEngine();

  void play(SoundID id) noexcept;

 private:
  SoundEngine();

  std::unordered_map<SoundID, UniquePtr<ctn::SoundEffect>> m_sounds;
};

}  // namespace albinjohansson::wanderer
