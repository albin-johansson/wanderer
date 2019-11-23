#include "catch.hpp"
#include "font.h"
#include "bad_state_exception.h"

using namespace albinjohansson::wanderer;

TEST_CASE("Font(string&, int)", "[Font]") {
  CHECK_THROWS_AS(Font("", 1), BadStateException);
  CHECK_THROWS_AS(Font("", 0), std::invalid_argument);
}

TEST_CASE("Font::Reset", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  f.SetBold(true);
  f.SetItalic(true);
  f.SetUnderlined(true);
  f.SetStrikethrough(true);

  f.Reset();
  CHECK(!f.IsBold());
  CHECK(!f.IsItalic());
  CHECK(!f.IsUnderlined());
  CHECK(!f.IsStrikethrough());
}

TEST_CASE("Font::SetBold", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.IsBold());

  f.SetBold(true);
  CHECK(f.IsBold());

  f.SetBold(false);
  CHECK(!f.IsBold());
}

TEST_CASE("Font::SetItalic", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.IsItalic());

  f.SetItalic(true);
  CHECK(f.IsItalic());

  f.SetItalic(false);
  CHECK(!f.IsItalic());
}

TEST_CASE("Font::SetUnderlined", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.IsUnderlined());

  f.SetUnderlined(true);
  CHECK(f.IsUnderlined());

  f.SetUnderlined(false);
  CHECK(!f.IsUnderlined());
}

TEST_CASE("Font::SetStrikethrough", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.IsStrikethrough());

  f.SetStrikethrough(true);
  CHECK(f.IsStrikethrough());

  f.SetStrikethrough(false);
  CHECK(!f.IsStrikethrough());
}

TEST_CASE("Font::SetOutlined", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);

  CHECK(!f.IsOutlined());

  f.SetOutlined(true);
  CHECK(f.IsOutlined());

  f.SetOutlined(false);
  CHECK(!f.IsOutlined());
}

TEST_CASE("Font::GetSize", "[Font]") {
  int size = 12;
  Font f("resources/font/type_writer.ttf", size);

  CHECK(size == f.GetSize());
}

TEST_CASE("Font::IsFixedWidth", "[Font]") {
  Font firacode("resources/font/fira_code.ttf", 12); // Fixed width
  Font daniel("resources/font/daniel.ttf", 12);      // Not fixed width

  CHECK(firacode.IsFixedWidth());
  CHECK(!daniel.IsFixedWidth());
}

TEST_CASE("Font::GetInternalFont", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);
  CHECK(f.GetInternalFont() != nullptr);
}

TEST_CASE("Font::GetFamilyName", "[Font]") {
  Font f("resources/font/type_writer.ttf", 12);
  CHECK(f.GetFamilyName() == "Type Writer");
}
