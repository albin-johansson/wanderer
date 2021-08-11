#include "parse_tile.hpp"

#include <cassert>              // assert
#include <centurion.hpp>        // irect, farea, ticks
#include <cstddef>              // size_t
#include <rune/everything.hpp>  // index_to_matrix

#include "core/aliases/maybe.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer::io {
namespace {

[[nodiscard]] auto to_source_rect(const int index,
                                  const int nColumns,
                                  const int tileWidth,
                                  const int tileHeight) noexcept -> cen::irect
{
  const auto [row, col] = rune::index_to_matrix(index, nColumns);
  return cen::irect{{col * tileWidth, row * tileHeight}, {tileWidth, tileHeight}};
}

void add_animation(ir::fancy_tile& tileData,
                   const rune::tmx_animation& animationData,
                   const tile_id firstGid)
{
  auto& animation = tileData.animation.emplace();

  animation.index = 0;
  animation.then = cen::counter::ticks();

  auto& frames = animation.frames;
  frames.reserve(animationData.frames.size());

  for (const auto& frameData : animationData.frames)
  {
    auto& frame = frames.emplace_back();
    frame.tile = firstGid + static_cast<tile_id>(frameData.tile.get());
    frame.duration = std::chrono::duration_cast<ms_t>(frameData.duration);
  }
}

void add_hitbox(ir::fancy_tile& tileData,
                const rune::tmx_object& object,
                const float xRatio,
                const float yRatio)
{
  const auto offset = float2{object.x * xRatio, object.y * yRatio};
  const auto size = cen::farea{object.width * xRatio, object.height * yRatio};
  tileData.hitbox = sys::make_hitbox({{offset, size}});
}

}  // namespace

auto make_tile(const tile_id id,
               const int index,
               const texture_id texture,
               const rune::tmx_tileset& tileset) -> ir::tile
{
  ir::tile data;

  data.id = id;
  data.texture = texture;
  data.source = to_source_rect(index,
                               tileset.column_count,
                               tileset.tile_width,
                               tileset.tile_height);

  return data;
}

auto parse_fancy_tile(ir::tileset& data,
                      const ir::tile& tileData,
                      const rune::tmx_tile& tile,
                      const tile_id firstGid) -> ir::fancy_tile
{
  ir::fancy_tile result;

  if (tile.animation)
  {
    add_animation(result, *tile.animation, firstGid);
  }

  if (tile.object_layer)
  {
    const auto& objectLayer = rune::tmx::get_object_layer(*tile.object_layer);

    // Only allow one object per tile for now
    assert(objectLayer.objects.size() == 1);

    const auto& object = objectLayer.objects.at(0);
    if (object.type == "Hitbox")
    {
      add_hitbox(result, object, data.x_ratio, data.y_ratio);
    }
  }

  if (const auto* depth = rune::tmx::get_if_int(tile.properties, "depth"))
  {
    result.depth = depth_t{*depth};
  }

  return result;
}

}  // namespace wanderer::io