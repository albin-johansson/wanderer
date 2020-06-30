#include "image_loader.h"

namespace wanderer {

auto ImageLoader::load(ctn::Renderer& renderer, std::string_view path) const
    -> std::shared_ptr<ctn::Texture>
{
  return ctn::Texture::shared(renderer, path.data());
}

}  // namespace wanderer
