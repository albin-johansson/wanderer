#include "tile.h"
#include "objects.h"

namespace albinjohansson::wanderer {

Tile::Tile(TileProperties properties) : properties(std::move(properties)) {}

Tile::~Tile() = default;

void Tile::Tick(ILevel& level) {}

void Tile::Draw(TilePos pos, Renderer& renderer, const Viewport& viewport) const {

}

}
