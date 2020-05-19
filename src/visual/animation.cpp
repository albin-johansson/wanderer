#include "animation.h"

#include "timer.h"

using namespace centurion;

namespace wanderer {

Animation::Animation() noexcept
{
  previous = Timer::millis();
}

Animation::~Animation() noexcept = default;

void Animation::update() noexcept
{
  const auto elapsed = Timer::millis() - previous;
  if (elapsed >= delay) {
    previous = Timer::millis();
    ++index;
    if (index >= nFrames) {
      index -= nFrames;
    }
  }
}

void Animation::reset() noexcept
{
  index = 0;
  previous = 0;
}

void Animation::set_delay(uint32 delay) noexcept
{
  this->delay = delay;
}

void Animation::set_frame(int frameIndex) noexcept
{
  index = frameIndex;
  if (index >= nFrames) {
    index -= nFrames;
  } else if (index < 0) {
    index = 0;
  }
}

void Animation::set_number_of_frames(int nFrames) noexcept
{
  if (nFrames > 0) {
    this->nFrames = nFrames;
  }
}

int Animation::get_index() const noexcept
{
  return index;
}

bool Animation::is_done() const noexcept
{
  return index == (nFrames - 1);
}

}  // namespace wanderer
