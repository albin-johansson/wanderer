#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

int main(int argc, char** argv)
{
  doctest::Context context;

  const auto result = context.run();

  if (context.shouldExit()) {
    return result;
  }

  return result;
}
