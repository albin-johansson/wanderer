#pragma once

#include "components/ui/menu.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::ctx {

struct active_menu final
{
  comp::menu::entity entity{null<comp::menu>()};
};

void serialize(auto& archive, active_menu& am)
{
  archive(am.entity);
}

}  // namespace wanderer::ctx
