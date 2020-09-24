#include "image_loader.hpp"

namespace wanderer {

auto image_loader::load(cen::renderer& renderer, std::string_view path) const
    -> std::shared_ptr<cen::texture>
{
  return std::make_shared<cen::texture>(renderer, path.data());
}

}  // namespace wanderer