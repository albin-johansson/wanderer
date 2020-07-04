#pragma once

#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer::comp {

struct AABB {
  vector2f min;  // the NW corner coordinates
  vector2f max;  // the SE corner coordinates
  vector2f center;
  float area{};
};

struct AABBNode {
  AABB box;
  entt::entity parent{entt::null};
  entt::entity left{entt::null};
  entt::entity right{entt::null};
};

struct AABBRoot {
};

}  // namespace wanderer::comp
