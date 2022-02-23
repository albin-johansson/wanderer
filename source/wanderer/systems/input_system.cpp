#include "input_system.hpp"

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

  if (moveUp && moveDown) {
    dispatcher.enqueue<stop_player_event>(direction_up_and_down);
  }
  else if (moveUp) {
    dispatcher.enqueue<move_player_event>(direction_up_bit);
  }
  else if (moveDown) {
    dispatcher.enqueue<move_player_event>(direction_down_bit);
  }

  if (moveLeft && moveRight) {
    dispatcher.enqueue<stop_player_event>(direction_left_and_right);
  }
  else if (moveLeft) {
    dispatcher.enqueue<move_player_event>(direction_left_bit);
  }
  else if (moveRight) {
    dispatcher.enqueue<move_player_event>(direction_right_bit);
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
  const auto entity = registry.view<comp::player>().front();
  auto& body = registry.get<comp::physics_body>(entity);

  auto velocity = body.data->GetLinearVelocity();

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

  body.data->SetLinearVelocity(glmx::as_b2(limited));
}

void on_stop_player(entt::registry& registry, const stop_player_event& event)
{
  const auto entity = registry.view<comp::player>().front();
  auto& body = registry.get<comp::physics_body>(entity);

  auto velocity = body.data->GetLinearVelocity();

  if (event.direction_mask | direction_left_and_right) {
    velocity.x = 0;
  }

  if (event.direction_mask | direction_up_and_down) {
    velocity.y = 0;
  }

  auto limited = glmx::from_b2(velocity);
  glmx::cap_magnitude(limited, body.max_speed);

  body.data->SetLinearVelocity(glmx::as_b2(limited));
}

}  // namespace wanderer::sys