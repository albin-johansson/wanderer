#include "sound_effect.h"
#include "bad_state_exception.h"

using namespace wanderer::core;

namespace wanderer::audio {

SoundEffect::SoundEffect(const std::string& file) {
  chunk = Mix_LoadWAV(file.c_str());
  if (chunk == nullptr) {
    throw BadStateException(SDL_GetError());
  }
  SetVolume(MIX_MAX_VOLUME / 2);
}

SoundEffect::~SoundEffect() {
  Stop();
  Mix_FreeChunk(chunk);
}

SoundEffect_uptr SoundEffect::Create(const std::string& file) {
  return std::make_unique<SoundEffect>(file);
}

void SoundEffect::Activate(int nLoops) noexcept {
  if (channel != UNDEFINED_CHANNEL) {
    Mix_PlayChannel(channel, chunk, nLoops);
  } else {
    channel = Mix_PlayChannel(UNDEFINED_CHANNEL, chunk, nLoops);
  }
}

void SoundEffect::Play() noexcept {
  Activate(0);
}

void SoundEffect::Loop(int nLoops) noexcept {
  if (nLoops < 0) {
    nLoops = -1;
  }

  Activate(nLoops);
}

void SoundEffect::Stop() noexcept {
  if (IsPlaying()) {
    Mix_Pause(channel);
    channel = UNDEFINED_CHANNEL;
  }
}

void SoundEffect::FadeIn(Uint32 ms) noexcept {
  if (ms > 0 && !IsPlaying()) {
    if (channel != UNDEFINED_CHANNEL) {
      Mix_FadeInChannelTimed(channel, chunk, 0, ms, -1);
    } else {
      channel = Mix_FadeInChannelTimed(UNDEFINED_CHANNEL, chunk, 0, ms, -1);
    }
  }
}

void SoundEffect::FadeOut(Uint32 ms) noexcept {
  if ((ms > 0) && IsPlaying()) {
    Mix_FadeOutChannel(channel, ms);
  }
}

void SoundEffect::SetVolume(int volume) noexcept {
  if (volume < 0) {
    volume = 0;
  }

  if (volume > MIX_MAX_VOLUME) {
    volume = MIX_MAX_VOLUME;
  }

  Mix_VolumeChunk(chunk, volume);
}

}
