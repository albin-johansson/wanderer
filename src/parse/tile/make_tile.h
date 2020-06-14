#pragma once

#include <rect.h>
#include <step.h>
#include <texture.h>

#include <memory>

#include "types.h"

namespace wanderer {

void parse_special_tile(entt::registry& registry,
                        entt::entity tileEntity,
                        const step::Tile& stepTile,
                        TileID firstgid);

[[nodiscard]] entt::entity make_basic_tile(
    entt::registry& registry,
    const TileID id,
    const std::shared_ptr<centurion::Texture>& sheet,
    const centurion::IRect& src);

}  // namespace wanderer
