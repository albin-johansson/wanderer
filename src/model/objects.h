#pragma once
#include <stdexcept>
#include <memory>

namespace wanderer::model {

class Objects final {
 public:
  Objects() = delete;

  ~Objects() = default;

  /**
   * Requires the supplied raw pointer to be non-null, otherwise an exception is thrown.
   *
   * \tparam T the type of the instance that the supplied pointer is pointing to.
   * \param ptr the raw pointer that will be checked.
   * \return the supplied raw pointer.
   * \throws invalid_argument if the supplied pointer is a null pointer.
   * \since 0.1.0
   */
  template<class T>
  inline static T* RequireNonNull(T* ptr) {
    if (ptr == nullptr) {
      throw std::invalid_argument("Null pointer!");
    } else {
      return ptr;
    }
  }

  /**
   * Requires the supplied unique pointer to be non-null, otherwise an exception is thrown.
   *
   * \tparam T the type parameter of the unique pointer.
   * \param ptr the unique pointer that will be checked.
   * \return the supplied unique pointer.
   * \throws invalid_argument if the supplied pointer is a null pointer.
   * \since 0.1.0
   */
  template<class T>
  inline static std::unique_ptr<T> RequireNonNull(std::unique_ptr<T> ptr) {
    if (ptr == nullptr) {
      throw std::invalid_argument("Null unique pointer!");
    } else {
      return ptr;
    }
  }

  /**
   * Requires the supplied shared pointer to be non-null, otherwise an exception is thrown.
   *
   * \tparam T the type parameter of the shared pointer.
   * \param ptr the shared pointer that will be checked.
   * \return the supplied shared pointer.
   * \throws invalid_argument if the supplied pointer is a null pointer.
   * \since 0.1.0
   */
  template<class T>
  inline static std::shared_ptr<T> RequireNonNull(std::shared_ptr<T> ptr) {
    if (ptr == nullptr) {
      throw std::invalid_argument("Null shared pointer!");
    } else {
      return ptr;
    }
  }
};

} // namespace wanderer::model