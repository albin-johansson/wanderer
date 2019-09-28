#include "gtest/gtest.h"
#include "vector_2.h"

using namespace wanderer::model;

class Vector2Test : public testing::Test {
 protected:
  Vector2 vector;

 public:
  static constexpr int X = 1952;
  static constexpr int Y = 8197;

  void SetUp() override {
//    vector.SetX(X);
//    vector.SetY(Y);
  }

  void TearDown() override {
  }
};

TEST_F(Vector2Test, Ctor) {
//  wanderer::model::Vector2 v;
//
//  v.SetX(3);

//  vector.SetX(2);
}

TEST_F(Vector2Test, Add) {
//  const int x2 = 2951;
//  const int y2 = 827;
//  Vector2 otherVec(x2, y2);
//
//  vector.Add(otherVec);
//
//  EXPECT_EQ((X + x2), vector.GetX());
//  EXPECT_EQ((Y + y2), vector.GetY());
//
//  EXPECT_EQ(x2, otherVec.GetX());
//  EXPECT_EQ(y2, otherVec.GetY());
}

TEST_F(Vector2Test, Sub) {

}

TEST_F(Vector2Test, Mul) {

}

TEST_F(Vector2Test, Scale) {

}

TEST_F(Vector2Test, SetMagnitude) {

}

TEST_F(Vector2Test, SetX) {

}

TEST_F(Vector2Test, SetY) {

}

TEST_F(Vector2Test, GetMagnitude) {

}

TEST_F(Vector2Test, GetX) {

}

TEST_F(Vector2Test, GetY) {

}