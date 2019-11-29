#include "catch.hpp"
#include "sprite_sheet.h"
#include "image.h"
#include "window.h"
#include "renderer.h"

using namespace albinjohansson::wanderer;

TEST_CASE("SpriteSheet::GetSource", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  SECTION("First source rectangle") {
    auto& rect = sheet.GetSource(sheet.GetMinId());

    CHECK(rect.GetX() == 0);
    CHECK(rect.GetY() == 0);
    CHECK(rect.GetWidth() == size);
    CHECK(rect.GetHeight() == size);
  }

//  SECTION("Misc source rectangle") {
//    auto i = (sheet.GetMaxID() - sheet.GetMinID()) / 2;
//
//    auto row = i / sheet.GetCols();
//    auto col = i % sheet.GetCols();
//
//    auto id = range.min + 10;
//    auto& rect = sheet.GetSource(id);
//
//    CHECK(rect.GetX() == col * size);
//    CHECK(rect.GetY() == row * size);
//    CHECK(rect.GetWidth() == size);
//    CHECK(rect.GetHeight() == size);
//  }

  SECTION("Last source rectangle") {
    auto& rect = sheet.GetSource(sheet.GetMaxId());

    CHECK(rect.GetX() == ((sheet.GetCols() - 1) * sheet.GetSpriteSize()));
    CHECK(rect.GetY() == ((sheet.GetRows() - 1) * sheet.GetSpriteSize()));
    CHECK(rect.GetWidth() == size);
    CHECK(rect.GetHeight() == size);
  }

}

TEST_CASE("SpriteSheet::GetMinId", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  CHECK(range.min == sheet.GetMinId());
}

TEST_CASE("SpriteSheet::GetMaxId", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  CHECK(range.max == sheet.GetMaxId());
}

TEST_CASE("SpriteSheet::GetRows", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  CHECK(img->GetHeight() / size == sheet.GetRows());
}

TEST_CASE("SpriteSheet::GetCols", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  CHECK(img->GetWidth() / size == sheet.GetCols());
}

TEST_CASE("SpriteSheet::Contains", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  CHECK(!sheet.Contains(range.min - 1));
  CHECK(!sheet.Contains(range.max + 1));

  CHECK(sheet.Contains(range.min));
  CHECK(sheet.Contains(range.max));
}

TEST_CASE("SpriteSheet::Contains", "[SpriteSheet]") {
  Window window("foo", 10, 10);
  Renderer renderer(window.GetInternalWindow());

  Image_sptr img = Image::Create(renderer.GetInternalRenderer(), "resources/img/outside.png");

  const Range range = {1, 1024};
  const int size = 32;

  auto sheet = SpriteSheet(img, range, size);

  CHECK(sheet.GetSpriteSize() == size);
}
