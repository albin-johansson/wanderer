#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

enum class TriggerType
{
  portal = 0,
  container = 1,
  bed = 2
};

struct Trigger final
{
  TriggerType type{};
};

struct IsWithinTrigger final
{
  entt::entity trigger_entity{entt::null};
};

}  // namespace wanderer::comp