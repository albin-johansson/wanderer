#include "tile_animation.h"

#include <SDL.h>

namespace wanderer {

TileAnimation::TileAnimation() = default;

TileAnimation::TileAnimation(int nFrames) : m_nFrames(nFrames)
{
  m_previous = SDL_GetTicks();
}

TileAnimation::~TileAnimation() = default;

void TileAnimation::update()
{
  uint32_t elapsed = SDL_GetTicks() - m_previous;
  if (elapsed >= get_frame().duration) {
    m_previous = SDL_GetTicks();
    ++m_index;
    if (m_index >= m_nFrames) {
      m_index -= m_nFrames;
    }
  }
}

void TileAnimation::set_frame(int index, Frame frame)
{
  if (!m_frames.count(index)) {
    m_frames.emplace(index, frame);
  }
}

Frame TileAnimation::get_frame() const
{
  return m_frames.at(m_index);
}

}  // namespace wanderer
