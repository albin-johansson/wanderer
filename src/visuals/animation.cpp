#include "animation.h"
#include "time_utils.h"
#include "require.h"

namespace albinjohansson::wanderer {

Animation::Animation() noexcept {
  previous = TimeUtils::get_millis();
}

Animation::~Animation() noexcept = default;

void Animation::update() noexcept {
  const auto elapsed = TimeUtils::get_millis() - previous;
  if (elapsed >= delay) {
    previous = TimeUtils::get_millis();
    ++index;
    if (index >= nFrames) {
      index -= nFrames;
    }
  }
}

void Animation::reset() noexcept {
  index = 0;
  previous = 0;
}

void Animation::set_delay(uint32_t delay) noexcept {
  this->delay = delay;
}

void Animation::set_frame(int frameIndex) noexcept {
  index = frameIndex;
  if (index >= nFrames) {
    index -= nFrames;
  } else if (index < 0) {
    index = 0;
  }
}

void Animation::set_number_of_frames(int nFrames) noexcept {
  if (nFrames > 0) {
    this->nFrames = nFrames;
  }
}

int Animation::get_index() const noexcept {
  return index;
}

bool Animation::is_done() const noexcept {
  return index == (nFrames - 1);
}

}
