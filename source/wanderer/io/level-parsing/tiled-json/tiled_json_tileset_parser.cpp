#include "tiled_json_tileset_parser.hpp"

#include "tiled_json_utils.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/io/json.hpp"
#include "wanderer/misc/exception.hpp"

namespace wanderer::io::tiled {
namespace {

void _parse_tileset_tiles_metadata(const nlohmann::json& tilesetJson,
                                   entt::registry& registry,
                                   const tile_id first,
                                   const glm::vec2& tileSizeRatio)
{
  const auto& tileset = registry.ctx<comp::Tileset>();

  for (const auto& [_, tileJson] : tilesetJson.at("tiles").items()) {
    const auto localId = tileJson.at("id").get<tile_id>();
    const auto globalId = first + localId;

    const auto tileEntity = tileset.tiles.at(globalId);

    auto& info = registry.get<comp::TileInfo>(tileEntity);
    info.depth_index = get_property<int32>(tileJson, "depth", info.depth_index);

    if (tileJson.contains("animation")) {
      auto& animation = registry.emplace<comp::Animation>(tileEntity);
      auto& tileAnimation = registry.emplace<comp::TileAnimation>(tileEntity);

      const auto arr = tileJson.at("animation");
      animation.frame_count = arr.size();

      animation.delays.reserve(animation.frame_count);
      tileAnimation.frames.reserve(animation.frame_count);

      for (const auto& [frameKey, frameJson] : arr.items()) {
        const auto tile = first + frameJson.at("tileid").get<tile_id>();
        const auto duration = frameJson.at("duration").get<uint64>();

        tileAnimation.frames.push_back(tile);
        animation.delays.emplace_back(duration);
      }
    }

    if (tileJson.contains("objectgroup")) {
      const auto& objects = tileJson.at("objectgroup").at("objects");

      if (objects.size() != 1) {
        throw_traced(WandererError{"Tiles must only feature one object!"});
      }

      const auto& objectJson = objects.at(0);

      auto& hitbox = registry.emplace<comp::TileHitbox>(tileEntity);
      hitbox.offset.x = objectJson.at("x").get<float32>() * tileSizeRatio.x;
      hitbox.offset.y = objectJson.at("y").get<float32>() * tileSizeRatio.y;
      hitbox.size.x = objectJson.at("width").get<float32>() * tileSizeRatio.x;
      hitbox.size.y = objectJson.at("height").get<float32>() * tileSizeRatio.y;
    }
  }
}

void _parse_common_tileset_attributes(const nlohmann::json& json,
                                      const std::filesystem::path& dir,
                                      const tile_id firstId,
                                      entt::registry& registry,
                                      Graphics& graphics)
{
  auto& tileset = registry.ctx<comp::Tileset>();

  const auto tileWidth = json.at("tilewidth").get<int32>();
  const auto tileHeight = json.at("tileheight").get<int32>();
  const auto columns = json.at("columns").get<int32>();

  const auto imagePath = dir / json.at("image").get<std::string>();
  const auto textureId = graphics.load_texture(imagePath);

  const auto count = json.at("tilecount").get<tile_id>();
  const auto end = firstId + count;

  tileset.tiles.reserve(tileset.tiles.bucket_count() + count);

  const auto humanoidLayerIndex = registry.ctx<comp::Tilemap>().humanoid_layer_index;
  int32 index = 0;

  for (tile_id id = firstId; id < end; ++id, ++index) {
    const auto entity = registry.create();
    tileset.tiles[id] = entity;

    auto& info = registry.emplace<comp::TileInfo>(entity);
    info.texture = textureId;
    info.depth_index = humanoidLayerIndex;

    const auto row = index / columns;
    const auto col = index % columns;

    info.source.x = col * tileWidth;
    info.source.y = row * tileHeight;
    info.source.z = tileWidth;
    info.source.w = tileHeight;
  }

  if (json.contains("tiles")) {
    const auto& cfg = registry.ctx<GameConfig>();
    const auto tileSizeRatio = cfg.tile_size / glm::vec2{tileWidth, tileHeight};

    _parse_tileset_tiles_metadata(json, registry, firstId, tileSizeRatio);
  }
}

}  // namespace

void parse_tileset(const nlohmann::json& json,
                   const std::filesystem::path& dir,
                   entt::registry& registry,
                   Graphics& graphics)
{
  const auto firstTileId = json.at("firstgid");
  if (json.contains("source")) {
    const auto path = dir / json.at("source");
    const auto external = read_json(path);
    _parse_common_tileset_attributes(external, dir, firstTileId, registry, graphics);
  }
  else {
    _parse_common_tileset_attributes(json, dir, firstTileId, registry, graphics);
  }
}

}  // namespace wanderer::io::tiled