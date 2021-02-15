#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <cen/centurion.hpp>

int main(int argc, char** argv)
{
  cen::library lib;
  return Catch::Session().run(argc, argv);
}
