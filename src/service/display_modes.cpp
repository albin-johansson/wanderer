#include "display_modes.h"
#include "bad_state_exception.h"

namespace albinjohansson::wanderer {

SDL_DisplayMode DisplayModes::GetDesktopInfo() {
  SDL_DisplayMode dm;
  if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
    throw BadStateException(SDL_GetError());
  }
  return dm;
}

}
