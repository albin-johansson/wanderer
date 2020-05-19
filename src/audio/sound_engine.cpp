#include "sound_engine.h"

#include "sound_effect.h"

using namespace centurion;

namespace wanderer {

SoundEngine::SoundEngine()
{}

SoundEngine::~SoundEngine() = default;

void SoundEngine::play(SoundID id) noexcept
{
  if (m_sounds.count(id)) {
    m_sounds[id]->play();
  }
}

}  // namespace wanderer
