#define CATCH_CONFIG_RUNNER
#include <centurion.h>

#include <catch.hpp>

int main(int argc, char** argv)
{
  using namespace centurion;
  Centurion c;
  return Catch::Session().run(argc, argv);
}