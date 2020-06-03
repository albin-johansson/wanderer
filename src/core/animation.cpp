#include "animation.h"

#include <timer.h>

using namespace centurion;

namespace wanderer {

void Animation::tick() noexcept
{
  const auto now = Timer::millis();
  const auto elapsed = now - m_then;
  if (elapsed >= m_delay) {
    m_then = now;
    ++m_frame;
    if (m_frame >= m_nFrames) {
      m_frame = 0;
    }
  }
}

void Animation::reset() noexcept
{
  m_frame = 0;
  m_then = Timer::millis();
}

void Animation::set_delay(u32 delay) noexcept
{
  m_delay = delay;
}

void Animation::set_frames(u32 frames) noexcept
{
  m_nFrames = frames;
}

}  // namespace wanderer
