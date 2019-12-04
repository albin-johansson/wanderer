#include "tiled_animation.h"

namespace albinjohansson::tiled {

TiledAnimation::TiledAnimation(int nFrames) {
  frames.reserve(nFrames);
}

TiledAnimation::~TiledAnimation() = default;

void TiledAnimation::AddFrame(int index, Frame frame) {
  frames.at(index) = frame;
}

}
