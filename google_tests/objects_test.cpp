#include "gtest/gtest.h"
#include "objects.h"

using namespace wanderer::model;

TEST(ObjectsTest, RawPointer) {
  int* ptr = nullptr;
  EXPECT_THROW(Objects::RequireNonNull(ptr), std::invalid_argument);
}

TEST(ObjectsTest, SharedPointer) {
  std::shared_ptr<int> ptr = nullptr;
  EXPECT_THROW(Objects::RequireNonNull(ptr), std::invalid_argument);
}

TEST(ObjectsTest, UniquePointer) {
  std::unique_ptr<int> ptr = nullptr;
  EXPECT_THROW(wanderer::model::Objects::RequireNonNull(std::move(ptr)), std::invalid_argument);
}