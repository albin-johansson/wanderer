#include "animation.h"
#include "time_utils.h"

namespace albinjohansson::wanderer {

Animation::Animation() noexcept {
  previous = TimeUtils::GetMillis();
}

Animation::~Animation() noexcept = default;

void Animation::Update() noexcept {
  const auto elapsed = TimeUtils::GetMillis() - previous;
  if (elapsed >= delay) {
    previous = TimeUtils::GetMillis();
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

void Animation::SetDelay(uint32_t delay) noexcept {
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

int Animation::GetIndex() const noexcept {
  return index;
}

bool Animation::IsDone() const noexcept {
  return index == (nFrames - 1);
}

}
