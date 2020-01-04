#include "tile_animation.h"
#include <SDL.h>

namespace albinjohansson::wanderer {

TileAnimation::TileAnimation() = default;

TileAnimation::TileAnimation(int nFrames) : nFrames(nFrames) {
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
    frames.emplace(index, frame);
  }
}

Frame TileAnimation::GetFrame() const {
  return frames.at(index);
}

}
