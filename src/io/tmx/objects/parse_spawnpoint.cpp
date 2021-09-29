#include "parse_spawnpoint.hpp"

#include <cassert>    // assert
#include <stdexcept>  // runtime_error

#include "core/game_constants.hpp"

namespace wanderer::io {
namespace {

[[nodiscard]] auto get_spawnpoint_entity(const rune::tmx_properties& properties)
    -> comp::spawnpoint_type
{
  const auto entity = rune::tmx::get_string(properties, "entity");
  if (entity == "player") {
    return comp::spawnpoint_type::player;
  }
  else if (entity == "skeleton") {
    return comp::spawnpoint_type::skeleton;
  }
  else {
    throw std::runtime_error{"Did not recognize spawnpoint type!"};
  }
}

}  // namespace

auto parse_spawnpoint(const rune::tmx_object& object,
                      const float xRatio,
                      const float yRatio) -> comp::spawnpoint
{
  assert(rune::tmx::is_string(object.properties, "entity"));
  comp::spawnpoint spawnpoint;

  spawnpoint.position = float2{object.x * xRatio, object.y * yRatio};
  spawnpoint.type = get_spawnpoint_entity(object.properties);

  // TODO only do this for humanoids, when animals are added
  spawnpoint.position.x -= glob::humanoid_draw_width / 2.0f;
  spawnpoint.position.y -= glob::humanoid_draw_height / 2.0f;

  return spawnpoint;
}

}  // namespace wanderer::io
