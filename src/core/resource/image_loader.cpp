#include "image_loader.h"

using ctn::Renderer;
using ctn::Texture;

namespace wanderer {

auto ImageLoader::load(Renderer& renderer, std::string_view path) const
    -> std::shared_ptr<Texture>
{
  return Texture::shared(renderer, path.data());
}

}  // namespace wanderer
