#include "resource.h"

#include <catch.hpp>

using namespace wanderer;

TEST_CASE("Resource::img", "[Resource]")
{
  CHECK_NOTHROW(Resource::img(nullptr));

  const auto name = "foo.png";
  const auto path = Resource::img(name);

  CHECK(!path.empty());
  CHECK(name == path.substr(path.find_last_of("/") + 1));
}

TEST_CASE("Resource::font", "[Resource]")
{
  CHECK_NOTHROW(Resource::font(nullptr));

  const auto name = "bar.ttf";
  const auto path = Resource::font(name);

  CHECK(!path.empty());
  CHECK(name == path.substr(path.find_last_of("/") + 1));
}

TEST_CASE("Resource::sfx", "[Resource]")
{
  CHECK_NOTHROW(Resource::sfx(nullptr));

  const auto name = "wow.wav";
  const auto path = Resource::sfx(name);

  CHECK(!path.empty());
  CHECK(name == path.substr(path.find_last_of("/") + 1));
}

TEST_CASE("Resource::map", "[Resource]")
{
  CHECK_NOTHROW(Resource::sfx(nullptr));

  const auto name = "vinewood.xml";
  const auto path = Resource::map(name);

  CHECK(!path.empty());
  CHECK(name == path.substr(path.find_last_of("/") + 1));
}

TEST_CASE("Resource::menu", "[Resource]")
{
  CHECK_NOTHROW(Resource::sfx(nullptr));

  const auto name = "lazer.json";
  const auto path = Resource::menu(name);

  CHECK(!path.empty());
  CHECK(name == path.substr(path.find_last_of("/") + 1));
}