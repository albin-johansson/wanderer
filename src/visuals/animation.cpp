#include "animation.h"

namespace albinjohansson::wanderer {

Animation::Animation() noexcept {
  index = 0;
  nFrames = 1;
  previous = SDL_GetTicks();
  delay = 100;
}

Animation::~Animation() noexcept = default;

void Animation::Update() noexcept {
  Uint32 elapsed = SDL_GetTicks() - previous;
  if (elapsed >= delay) {
    previous = SDL_GetTicks();
    ++index;
    if (index >= nFrames) {
      index -= nFrames;
    }
  }
}

void Animation::Reset() noexcept {
  index = 0;
  previous = 0;
}

void Animation::SetDelay(Uint32 delay) noexcept {
  this->delay = delay;
}

void Animation::SetFrame(int frameIndex) noexcept {
  index = frameIndex;
  if (index >= nFrames) {
    index -= nFrames;
  } else if (index < 0) {
    index = 0;
  }
}

void Animation::SetNumberOfFrames(int nFrames) noexcept {
  this->nFrames = nFrames; // TODO guard for valid input?
}

}
