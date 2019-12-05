#include "tile_animation.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

TileAnimation::TileAnimation(int nFrames) : nFrames(nFrames) {
  frames.reserve(nFrames);
  index = 0;
  previous = SDL_GetTicks();
}

TileAnimation::~TileAnimation() = default;

void TileAnimation::Update() {
  uint32_t elapsed = SDL_GetTicks() - previous;
  if (elapsed >= GetFrame().duration) {
    previous = SDL_GetTicks();
    ++index;
    if (index >= nFrames) {
      index -= nFrames;
    }
  }
}

void TileAnimation::SetFrame(int index, Frame frame) {
  if (!frames.count(index)) {
    frames.insert(std::pair<int, Frame>(index, frame));
  }
}

Frame TileAnimation::GetFrame() const {
  return frames.at(index);
}

}
