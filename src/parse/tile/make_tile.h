#pragma once

#include <rect.h>
#include <step.h>
#include <texture.h>

#include <memory>

#include "wanderer_stdinc.h"

namespace wanderer {

void parse_special_tile(entt::registry& registry,
                        entt::entity tileEntity,
                        const step::Tile& stepTile,
                        TileID firstGID);

[[nodiscard]] entt::entity make_basic_tile(
    entt::registry& registry,
    const TileID id,
    const entt::handle<centurion::Texture>& sheet,
    const centurion::IRect& src) noexcept;

}  // namespace wanderer
