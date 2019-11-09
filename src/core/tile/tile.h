#pragma once

namespace wanderer::core {

class Tile {
 private:
  int row;
  int col;
  int id;

 public:
  Tile(int row, int col, int id);

  ~Tile() = default;

  [[nodiscard]] inline int GetRow() const noexcept { return row; }

  [[nodiscard]] inline int GetCol() const noexcept { return col; }

  [[nodiscard]] inline int GetId() const noexcept { return id; }
};

}
