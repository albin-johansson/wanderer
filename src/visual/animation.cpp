#include "animation.h"

#include "timer.h"

using namespace centurion;

namespace wanderer {

Animation::Animation() noexcept
{
  m_previous = Timer::millis();
}

Animation::~Animation() noexcept = default;

void Animation::update() noexcept
{
  const auto elapsed = Timer::millis() - m_previous;
  if (elapsed >= m_delay) {
    m_previous = Timer::millis();
    ++m_index;
    if (m_index >= m_nFrames) {
      m_index -= m_nFrames;
    }
  }
}

void Animation::reset() noexcept
{
  m_index = 0;
  m_previous = 0;
}

void Animation::set_delay(uint32 delay) noexcept
{
  this->m_delay = delay;
}

void Animation::set_frame(int frameIndex) noexcept
{
  m_index = frameIndex;
  if (m_index >= m_nFrames) {
    m_index -= m_nFrames;
  } else if (m_index < 0) {
    m_index = 0;
  }
}

void Animation::set_number_of_frames(int nFrames) noexcept
{
  if (nFrames > 0) {
    this->m_nFrames = nFrames;
  }
}

int Animation::get_index() const noexcept
{
  return m_index;
}

bool Animation::is_done() const noexcept
{
  return m_index == (m_nFrames - 1);
}

}  // namespace wanderer
