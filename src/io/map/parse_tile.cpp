#include "parse_tile.hpp"

#include <cassert>  // assert
#include <centurion.hpp>
#include <cstddef>  // size_t

#include "hitbox_system.hpp"
#include "index_to_matrix.hpp"
#include "maybe.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto to_source_rect(const int index,
                                  const int nColumns,
                                  const int tileWidth,
                                  const int tileHeight) noexcept -> cen::irect
{
  const auto [row, col] = index_to_matrix(index, nColumns);
  return cen::irect{{col * tileWidth, row * tileHeight},
                    {tileWidth, tileHeight}};
}

void add_animation(ir::fancy_tile& tileData,
                   const step::animation& stepAnimation,
                   const tile_id firstGid)
{
  auto& animation = tileData.animation.emplace();

  animation.index = 0;
  animation.then = cen::counter::ticks();

  auto& frames = animation.frames;
  frames.reserve(static_cast<std::size_t>(stepAnimation.num_frames()));

  for (const auto& stepFrame : stepAnimation.frames())
  {
    auto& frame = frames.emplace_back();
    frame.tile = firstGid + static_cast<tile_id>(stepFrame.tile_id().get());
    frame.duration = ms_t{stepFrame.duration()};
  }
}

void add_hitbox(ir::fancy_tile& tileData,
                const step::object& object,
                const float xRatio,
                const float yRatio)
{
  const float2 offset{static_cast<float>(object.x()) * xRatio,
                      static_cast<float>(object.y()) * yRatio};

  const cen::farea size{static_cast<float>(object.width()) * xRatio,
                        static_cast<float>(object.height()) * yRatio};

  tileData.hitbox = sys::create_hitbox({{offset, size}});
}

[[nodiscard]] auto parse_depth(const step::properties& props) -> maybe<depth_t>
{
  if (props.has("depth"))
  {
    assert(props.get("depth").is<int>());
    return depth_t{props.get("depth").get<int>()};
  } else
  {
    return std::nullopt;
  }
}

}  // namespace

auto make_tile(const tile_id id,
               const int index,
               const texture_id texture,
               const step::tileset& tileset) -> ir::tile
{
  ir::tile data;

  data.id = id;
  data.texture = texture;
  data.source = to_source_rect(index,
                               tileset.columns(),
                               tileset.tile_width(),
                               tileset.tile_height());

  return data;
}

auto parse_fancy_tile(ir::tileset& data,
                      const ir::tile& tileData,
                      const step::tile& stepTile,
                      const tile_id firstGid) -> ir::fancy_tile
{
  ir::fancy_tile result;

  if (const auto& stepAnimation = stepTile.get_animation())
  {
    add_animation(result, *stepAnimation, firstGid);
  }

  if (const auto* layer = stepTile.object_group())
  {
    if (const auto* group = layer->try_as<step::object_group>())
    {
      // Only allow one object per tile for now
      assert(group->objects().size() == 1);
      const auto& object = group->objects().at(0);
      if (object.type() == "Hitbox")
      {
        add_hitbox(result, object, data.xRatio, data.yRatio);
      }
    }
  }

  if (const auto* props = stepTile.get_properties())
  {
    if (const auto depth = parse_depth(*props))
    {
      result.depth = *depth;
    }
  }

  return result;
}

}  // namespace wanderer