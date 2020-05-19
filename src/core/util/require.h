#pragma once
#include <memory>
#include <stdexcept>

namespace albinjohansson::wanderer {

/**
 * The Require class provides utility methods related to different kinds of
 * requirements, such as fail-fast null checks.
 *
 * @since 0.1.0
 */
class Require final {
 public:
  /**
   * The NullPointerException class is a subclass of std::exception that
   * describes an exception caused by supplying a null pointer to one of the
   * RequireNonNull methods.
   *
   * @since 0.1.0
   */
  class NullPointerException final : public std::exception {
   public:
    NullPointerException() : std::exception() {}
  };

  Require() = delete;

  ~Require() = default;

  /**
   * Requires that the supplied raw pointer isn't a null pointer.
   *
   * @tparam T the type of the pointer that will be checked.
   * @param pointer the pointer that will be checked.
   * @return the supplied pointer.
   * @throws NullPointerException if the supplied pointer is a null pointer.
   * @since 0.1.0
   */
  template <class T>
  inline static T* not_null(T* pointer)
  {
    if (pointer == nullptr) {
      throw NullPointerException();
    } else {
      return pointer;
    }
  }

  /**
   * Requires that the supplied unique pointer isn't a null pointer.
   *
   * @tparam T the type of the pointer that will be checked.
   * @param uniquePtr the unique pointer that will be checked.
   * @return the supplied pointer.
   * @throws NullPointerException if the supplied pointer is a null pointer.
   * @since 0.1.0
   */
  template <class T>
  inline static std::unique_ptr<T> not_null(std::unique_ptr<T> uniquePtr)
  {
    if (uniquePtr == nullptr) {
      throw NullPointerException();
    } else {
      return uniquePtr;
    }
  }

  /**
   * Requires that the supplied shared pointer isn't a null pointer.
   *
   * @tparam T the type of the pointer that will be checked.
   * @param sharedPtr the shared pointer that will be checked.
   * @return the supplied pointer.
   * @throws NullPointerException if the supplied pointer is a null pointer.
   * @since 0.1.0
   */
  template <class T>
  inline static const std::shared_ptr<T>& not_null(
      const std::shared_ptr<T>& sharedPtr)
  {
    if (sharedPtr == nullptr) {
      throw NullPointerException();
    } else {
      return sharedPtr;
    }
  }
};

}  // namespace albinjohansson::wanderer