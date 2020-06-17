#include "image_loader.h"

using centurion::Renderer;
using centurion::Texture;

namespace wanderer {

std::shared_ptr<Texture> ImageLoader::load(Renderer& renderer,
                                           std::string_view path) const
{
  return Texture::shared(renderer, path.data());
}

}  // namespace wanderer
