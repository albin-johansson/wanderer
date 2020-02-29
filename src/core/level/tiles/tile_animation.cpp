#include "tile_animation.h"

#include <SDL.h>

namespace albinjohansson::wanderer {

TileAnimation::TileAnimation() = default;

TileAnimation::TileAnimation(int nFrames) : nFrames(nFrames)
{
  previous = SDL_GetTicks();
}

TileAnimation::~TileAnimation() = default;

void TileAnimation::update()
{
  uint32_t elapsed = SDL_GetTicks() - previous;
  if (elapsed >= get_frame().duration) {
    previous = SDL_GetTicks();
    ++index;
    if (index >= nFrames) {
      index -= nFrames;
    }
  }
}

void TileAnimation::set_frame(int index, Frame frame)
{
  if (!frames.count(index)) {
    frames.emplace(index, frame);
  }
}

Frame TileAnimation::get_frame() const
{
  return frames.at(index);
}

}  // namespace albinjohansson::wanderer
