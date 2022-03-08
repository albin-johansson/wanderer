#include "input_system.hpp"

#include "animation_system.hpp"
#include "physics_system.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/core/math.hpp"
#include "wanderer/data/components/tags.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/events/player_events.hpp"

namespace wanderer::sys {
namespace {

// TODO make customizable
constexpr cen::scan_code move_up_key = cen::scancodes::w;
constexpr cen::scan_code move_down_key = cen::scancodes::s;
constexpr cen::scan_code move_right_key = cen::scancodes::d;
constexpr cen::scan_code move_left_key = cen::scancodes::a;

}  // namespace

void update_input(entt::dispatcher& dispatcher, const input_state& input)
{
  const auto moveUp = input.is_pressed(move_up_key);
  const auto moveDown = input.is_pressed(move_down_key);
  const auto moveLeft = input.is_pressed(move_left_key);
  const auto moveRight = input.is_pressed(move_right_key);

  uint32 mask = 0;

  if (moveUp && moveDown) {
    dispatcher.enqueue<stop_player_event>(direction_up_and_down);
  }
  else if (moveUp) {
    mask |= direction_up_bit;
  }
  else if (moveDown) {
    mask |= direction_down_bit;
  }

  if (moveLeft && moveRight) {
    dispatcher.enqueue<stop_player_event>(direction_left_and_right);
  }
  else if (moveLeft) {
    mask |= direction_left_bit;
  }
  else if (moveRight) {
    mask |= direction_right_bit;
  }

  if (mask != 0) {
    dispatcher.enqueue<move_player_event>(mask);
  }

  if (input.was_released(move_up_key)) {
    dispatcher.enqueue<stop_player_event>(direction_up_bit);
  }

  if (input.was_released(move_down_key)) {
    dispatcher.enqueue<stop_player_event>(direction_down_bit);
  }

  if (input.was_released(move_left_key)) {
    dispatcher.enqueue<stop_player_event>(direction_left_bit);
  }

  if (input.was_released(move_right_key)) {
    dispatcher.enqueue<stop_player_event>(direction_right_bit);
  }
}

void on_move_player(entt::registry& registry, const move_player_event& event)
{
  const auto entity = registry.view<comp::Player>().front();
  auto& body = registry.get<comp::PhysicsBody>(entity);

  auto velocity = body.data->GetLinearVelocity();
  const auto prevVelocity = glmx::from_b2(velocity);

  if (event.direction_mask & direction_up_bit) {
    velocity.y = -body.max_speed;
  }
  else if (event.direction_mask & direction_down_bit) {
    velocity.y = body.max_speed;
  }

  if (event.direction_mask & direction_right_bit) {
    velocity.x = body.max_speed;
  }
  else if (event.direction_mask & direction_left_bit) {
    velocity.x = -body.max_speed;
  }

  auto limited = glmx::from_b2(velocity);
  glmx::cap_magnitude(limited, body.max_speed);

  /* Only update animation states if the direction changed */
  if (!glmx::is_zero(limited) && !glmx::is_zero(prevVelocity - limited)) {
    uint32 mask{};

    if (limited.x > 0) {
      mask |= direction_right_bit;
    }
    else if (limited.x < 0) {
      mask |= direction_left_bit;
    }

    if (limited.y > 0) {
      mask |= direction_down_bit;
    }
    else if (limited.y < 0) {
      mask |= direction_up_bit;
    }

    enter_humanoid_walk_animation(registry, entity, mask);
  }

  body.data->SetLinearVelocity(glmx::as_b2(limited));
}

void on_stop_player(entt::registry& registry, const stop_player_event& event)
{
  const auto entity = registry.view<comp::Player>().front();
  auto& body = registry.get<comp::PhysicsBody>(entity);

  auto velocity = body.data->GetLinearVelocity();
  const auto prevVelocity = glmx::from_b2(velocity);

  if (event.direction_mask | direction_left_and_right) {
    velocity.x = 0;
  }

  if (event.direction_mask | direction_up_and_down) {
    velocity.y = 0;
  }

  auto limited = glmx::from_b2(velocity);
  glmx::cap_magnitude(limited, body.max_speed);

  if (glmx::is_zero(limited)) {
    enter_humanoid_idle_animation(registry, entity, direction_left_bit);  // TODO
  }

  body.data->SetLinearVelocity(glmx::as_b2(limited));
}

}  // namespace wanderer::sys