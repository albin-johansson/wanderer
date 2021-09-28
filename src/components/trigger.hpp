#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

enum class trigger_type
{
  portal = 0,
  container = 1,
  bed = 2
};

struct trigger final
{
  trigger_type type{};
};

struct is_within_trigger final
{
  entt::entity trigger_entity{entt::null};
};

void serialize(auto& archive, trigger& t)
{
  archive(t.type);
}

}  // namespace wanderer::comp