//#include "catch.hpp"
//#include "tvector.h"
//#include "math.h"
//#include <cmath>
//
// using namespace wanderer::experimental;
// using namespace wanderer;
//
// namespace {
//
// template<typename T>
// void ctor() {
//  const Vector2<T> vector;
//  CHECK(vector.x == 0);
//  CHECK(vector.y == 0);
//  CHECK(vector.is_zero());
//}
//
// template<typename T>
// void ctor(const T x, const T y) {
//  const Vector2<T> vector{x, y};
//  CHECK(vector.x == x);
//  CHECK(vector.y == y);
//  CHECK(!vector.is_zero());
//}
//
// template<typename T>
// void copy_ctor(const T x, const T y) {
//  const Vector2<T> vector{x, y};
//  const Vector2<T> copy{vector};
//  CHECK(vector.x == copy.x);
//  CHECK(vector.y == copy.y);
//  CHECK(vector == copy);
//  CHECK(copy == vector);
//}
//
// template<typename T>
// void scale(const T x, const T y) {
//  Vector2<T> vector{x, y};
//
//  const auto factor = 3;
//  vector.scale(factor);
//
//  CHECK(vector.x == Approx(x * factor));
//  CHECK(vector.y == Approx(y * factor));
//
//  vector.scale(0);
//  CHECK(vector.is_zero());
//}
//
// template<typename T>
// void plusOperator(Vector2<T> lhs, Vector2<T> rhs) {
//  const Vector2<T> res1 = lhs + rhs;
//  const Vector2<T> res2 = rhs + lhs;
//  CHECK(((res1.x == (lhs.x + rhs.x)) && (res2.x == (lhs.x + rhs.x))));
//  CHECK(((res1.y == (lhs.y + rhs.y)) && (res2.y == (lhs.y + rhs.y))));
//}
//
// template<typename T>
// void minusOperator(const Vector2<T> lhs, const Vector2<T> rhs) {
//  SECTION("Normal operator test") {
//    const auto res = lhs - rhs;
//    CHECK(res.x == (lhs.x - rhs.x));
//    CHECK(res.y == (lhs.y - rhs.y));
//  }
//
//  SECTION("Reversed operands") {
//    const auto res = rhs - lhs;
//    CHECK(res.x == (rhs.x - lhs.x));
//    CHECK(res.y == (rhs.y - lhs.y));
//  }
//}
//
// template<typename T>
// void equalsOperator(Vector2<T> lhs, Vector2<T> rhs) {
//  const auto lhsCopy = Vector2<T>{lhs};
//  CHECK(lhs == lhs);
//  CHECK(lhs == lhsCopy);
//
//  CHECK(lhs == rhs);
//  CHECK(rhs == lhs);
//}
//
// template<typename T>
// void notEqualsOperator(Vector2<T> lhs, Vector2<T> rhs) {
//  CHECK(lhs != rhs);
//
//  const auto copy{lhs};
//  CHECK(!(lhs != copy));
//}
//
// template<typename T>
// void add(Vector2<T> lhs, Vector2<T> rhs) {
//  const auto expectedX = lhs.x + rhs.x;
//  const auto expectedY = lhs.y + rhs.y;
//
//  lhs.add(rhs);
//  CHECK(lhs.x == expectedX);
//  CHECK(lhs.y == expectedY);
//}
//
// template<typename T>
// void add(Vector2<T> vector, T dx, T dy) {
//  const auto x = vector.x;
//  const auto y = vector.y;
//
//  vector.add(dx, dy);
//  CHECK(vector.x == Approx(x + dx));
//  CHECK(vector.y == Approx(y + dy));
//}
//
// template<typename T>
// void sub(Vector2<T> lhs, Vector2<T> rhs) {
//  const auto x = lhs.x;
//  const auto y = lhs.y;
//
//  lhs.sub(rhs);
//  CHECK(lhs.x == Approx(x - rhs.x));
//  CHECK(lhs.y == Approx(y - rhs.y));
//}
//
// template<typename T>
// void sub(Vector2<T> vector, T dx, T dy) {
//  const auto x = vector.x;
//  const auto y = vector.y;
//
//  vector.sub(dx, dy);
//  CHECK(vector.x == Approx(x - dx));
//  CHECK(vector.y == Approx(y - dy));
//}
//
// template<typename T>
// void norm(Vector2<T> vector) {
//  vector.norm();
//  CHECK(vector.is_unit());
//  CHECK(vector.get_magnitude() == Approx(1));
//}
//
//}
//
// TEST_CASE("Vector2()", "[Vector2<T>]") {
//  ctor<float>();
//  ctor<int>();
//}
//
// TEST_CASE("Vector2(T, T)", "[Vector2<T>]") {
//  ctor<float>(53.8f, 125.2f);
//  ctor<int>(831, 455);
//}
//
// TEST_CASE("Vector2(Vector2&)", "[Vector2<T>]") {
//  copy_ctor<float>(87.3f, 39.5f);
//  copy_ctor<int>(3501, 281);
//}
//
// TEST_CASE("Vector2f::scale", "[Vector2<T>]") {
//  scale<float>(24.5f, 83.7f);
//  scale<int>(351, 7712);
//}
//
// TEST_CASE("Vector2f::operator+", "[Vector2<T>]") {
//  plusOperator<float>({123.4f, 614.9f}, {981.1f, -234.7f});
//  plusOperator<int>({7282, 9394}, {84, 819});
//}
//
// TEST_CASE("Vector2f::operator-", "[Vector2<T>]") {
//  minusOperator<float>({517.9f, 1774.0f}, {181.1f, 734.2f});
//  minusOperator<int>({482, 912}, {112, 772});
//}
//
// TEST_CASE("Vector2f::operator==", "[Vector2<T>]") {
//  equalsOperator<float>({712.8f, 913.3f}, {712.8f, 913.3f});
//  equalsOperator<int>({8192, 931}, {8192, 931});
//}
//
// TEST_CASE("Vector2f::operator!=", "[Vector2<T>]") {
//  notEqualsOperator<float>({389.4f, 4143.3f}, {-133.3f, 471.5f});
//  notEqualsOperator<int>({8192, 8433}, {1192, -421});
//}
//
// TEST_CASE("Vector2f::add(Vector2&)", "[Vector2<T>]") {
//  add<float>({105.3f, 83.2f}, {23.8f, 17.7f});
//  add<int>({-31, 21}, {15, 99});
//}
//
// TEST_CASE("Vector2f::add(T, T)", "[Vector2<T>]") {
//  add<float>({44.1f, 38.6f}, -29.2f, 12.8f);
//  add<int>({103, 89}, -25, 39);
//}
//
// TEST_CASE("Vector2f::sub(Vector2&)", "[Vector2<T>]") {
//  sub<float>({24.5f, 83.7f}, {88.2f, 24.8f});
//  sub<int>({18, 82}, {-5, 27});
//}
//
// TEST_CASE("Vector2f::norm", "[Vector2<T>]") {
//  norm<float>({12.0f, 92.3f});
//  norm<int>({17, 29});
//}
//
// TEST_CASE("Vector2f::zero", "[Vector2<T>]") {
//  Vector2f vector{859.0f, 229.3f};
//
//  vector.zero();
//  CHECK(vector.is_zero());
//}
//
// TEST_CASE("Vector2f::set", "[Vector2<T>]") {
//  Vector2f vector{91, 3};
//  Vector2f other{123, 45};
//
//  vector.set(other);
//
//  CHECK(vector.x == Approx(other.x));
//  CHECK(vector.y == Approx(other.y));
//}
//
// TEST_CASE("Vector2f::set_magnitude", "[Vector2<T>]") {
//  Vector2f vector{52, 93};
//
//  const float length = 4;
//  vector.set_magnitude(length);
//  CHECK(vector.get_magnitude() == Approx(length));
//}
//
// TEST_CASE("Vector2f::look_at(Vector2f, float)", "[Vector2<T>]") {
//  Vector2f vector{412, 287};
//
//  CHECK_NOTHROW(vector.look_at(vector, 0));
//  CHECK_NOTHROW(vector.look_at(vector, -1));
//}
//
// TEST_CASE("Vector2f::distance_to", "[Vector2<T>]") {
//  const Vector2f vector{377, 518};
//  const Vector2f other{123, 411};
//
//  const auto dx = other.x - vector.x;
//  const auto dy = other.y - vector.y;
//  const auto expected = std::sqrt(dx * dx + dy * dy);
//
//  CHECK(expected == vector.distance_to(other));
//  CHECK(vector.distance_to(other) == other.distance_to(vector));
//  CHECK(vector.distance_to(vector) == 0);
//}
//
// TEST_CASE("Vector2f::distance_to_2", "[Vector2<T>]") {
//  const Vector2f vector{58, 83};
//  const Vector2f other{284, 550};
//
//  CHECK(std::sqrt(vector.distance_to_2(other)) == vector.distance_to(other));
//  CHECK(vector.distance_to_2(vector) == 0);
//}
//
// TEST_CASE("Vector2f::angle", "[Vector2<T>]") {
//  const Vector2f nx{-1, 0};
//  const Vector2f ny{0, -1};
//
//  static constexpr Vector2f xUnit{1, 0};
//  static constexpr Vector2f yUnit{0, 1};
//
//  CHECK(xUnit.angle(yUnit) == 90);
//  CHECK(yUnit.angle(xUnit) == 90);
//  CHECK(xUnit.angle(ny) == 90);
//  CHECK(yUnit.angle(nx) == 90);
//
//  CHECK(xUnit.angle(xUnit) == 0);
//
//  SECTION("Maximum possible angle") {
//    CHECK(nx.angle(xUnit) == 180);
//    CHECK(xUnit.angle(nx) == 180);
//  }
//
//  SECTION("1 degree step") {
//    Vector2f vec{std::cos(Math::to_radians(1.0f)),
//                 std::sin(Math::to_radians(1.0f))};
//    CHECK(xUnit.angle(vec) == 1);
//  }
//}
//
// TEST_CASE("Vector2f::negate", "[Vector2<T>]") {
//  const auto x = 4;
//  const auto y = 8;
//
//  Vector2f vector{x, y};
//  vector.negate();
//
//  CHECK(vector.x == -x);
//  CHECK(vector.y == -y);
//}
//
// TEST_CASE("Vector2f::get_magnitude", "[Vector2<T>]") {
//  Vector2f vector;
//
//  CHECK(vector.get_magnitude() == 0);
//  CHECK(vector.is_zero());
//}
//
// TEST_CASE("Vector2f::get_magnitude_2", "[Vector2<T>]") {
//  Vector2f vector;
//
//  CHECK(vector.get_magnitude_2() == 0);
//  CHECK(vector.is_zero());
//}
//
// TEST_CASE("Vector2f::is_zero", "[Vector2<T>]") {
//  const Vector2f first;
//  CHECK(first.is_zero());
//
//  const Vector2f other{12, 95};
//  CHECK(!other.is_zero());
//}
//
// TEST_CASE("Vector2f::is_unit", "[Vector2<T>]") {
//  Vector2f vector{1, 0};
//  CHECK(vector.is_unit());
//
//  vector.scale(0.5f);
//  CHECK(!vector.is_unit());
//
//  vector.norm();
//  CHECK(vector.is_unit());
//}
