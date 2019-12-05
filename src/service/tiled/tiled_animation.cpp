#include "tiled_animation.h"

namespace albinjohansson::tiled {

TiledAnimation::TiledAnimation() = default;

TiledAnimation::TiledAnimation(int nFrames) {
  frames.reserve(nFrames);
}

TiledAnimation::~TiledAnimation() = default;

void TiledAnimation::AddFrame(Frame frame) {
  frames.push_back(frame);
}

const std::vector<Frame>& TiledAnimation::GetFrames() {
  return frames;
}

}
