#pragma once

#include <array>             // array
#include <cassert>           // assert
#include <cstddef>           // size_t
#include <initializer_list>  // initializer_list
#include <stdexcept>         // invalid_argument, runtime_error
#include <utility>           // move

namespace wanderer {

/**
 * \brief A data structure with an API similar to that of `std::vector`, but the elements
 * are stored in a `std::array`, i.e. as a part of the object.
 *
 * \note This class performs no dynamic memory allocations by itself.
 *
 * \ingroup core
 *
 * \tparam T the type of the elements.
 * \tparam Capacity the maximum capacity of the vector.
 */
template <typename T, std::size_t Capacity>
class static_vector final
{
 public:
  using size_type = std::size_t;
  using value_type = T;
  using iterator = value_type*;
  using const_iterator = const value_type*;

  /// Creates an empty vector.
  constexpr static_vector() = default;

  /**
   * \brief Creates a vector with the specified elements.
   *
   * \pre The size of the supplied list must not exceed the capacity of the vector.
   *
   * \details A terse way to use this constructor is using CTAD.
   * \code{cpp}
   *   static_vector vector = {1, 2, 3}; // decltype(vector) == static_vector<int, 3>
   * \endcode
   *
   * \param list the list of elements.
   */
  constexpr static_vector(std::initializer_list<value_type> list)
  {
    const auto size = list.size();
    assert(size <= Capacity);

    for (size_type index = 0u; auto value : list)
    {
      m_data.at(index) = std::move(value);
      ++index;
    }

    m_size = size;
  }

  /// Clears the vector.
  constexpr void clear() noexcept
  {
    m_size = 0;
  }

  /**
   * \brief Adds an element to the end of the vector.
   *
   * \param value the element that will be added.
   *
   * \throws runtime_error if the vector is full.
   */
  constexpr void push_back(const value_type& value)
  {
    const auto index = m_size;
    if (index < Capacity)
    {
      m_data.at(index) = value;
      ++m_size;
    }
    else
    {
      throw std::runtime_error{"static_vector::push_back(): vector already full!"};
    }
  }

  /// \copydoc push_back()
  constexpr void push_back(value_type&& value)
  {
    const auto index = m_size;
    if (index < Capacity)
    {
      m_data.at(index) = std::move(value);
      ++m_size;
    }
    else
    {
      throw std::runtime_error{"static_vector::push_back(): vector already full!"};
    }
  }

  /**
   * \brief Adds an element to the end of the vector, creating it from the supplied
   * arguments.
   *
   * \tparam Args the types of the arguments that will be forwarded.
   *
   * \param args the arguments that will be forwarded to an appropriate value constructor.
   *
   * \return a reference to the created element.
   *
   * \throws runtime_error if the vector is already full.
   */
  template <typename... Args>
  constexpr decltype(auto) emplace_back(Args&&... args)
  {
    const auto index = m_size;
    if (index < Capacity)
    {
      m_data.at(index) = value_type{std::forward<Args>(args)...};
      ++m_size;
      return m_data.at(index);
    }
    else
    {
      throw std::runtime_error{"static_vector::emplace_back(): vector already full!"};
    }
  }

  /**
   * \brief Removes the last element of the vector.
   *
   * \pre The vector must not be empty.
   */
  constexpr void pop_back() noexcept
  {
    assert(!empty());
    --m_size;
  }

  /**
   * \brief Returns the element at the specified index.
   *
   * \param index the index of the desired element.
   *
   * \return the element at the specified index.
   *
   * \throws invalid_argument if the index is out of bounds.
   */
  [[nodiscard]] constexpr auto at(const size_type index) -> value_type&
  {
    if (index < m_size)
    {
      return m_data.at(index);
    }
    else
    {
      throw std::invalid_argument{"static_vector::at(): invalid index!"};
    }
  }

  /// \copydoc at()
  [[nodiscard]] constexpr auto at(const size_type index) const -> const value_type&
  {
    if (index < m_size)
    {
      return m_data.at(index);
    }
    else
    {
      throw std::invalid_argument{"static_vector::at(): invalid index!"};
    }
  }

  /**
   * \brief Returns the element at the specified index.
   *
   * \note This function performs no bounds checking.
   *
   * \pre `index` must not be out of bounds.
   *
   * \param index the index of the desired element.
   *
   * \return the element at the specified index.
   */
  [[nodiscard]] constexpr auto operator[](const size_type index) noexcept -> value_type&
  {
    assert(index < m_size);
    return m_data[index];
  }

  /// \copydoc operator[]()
  [[nodiscard]] constexpr auto operator[](const size_type index) const noexcept
      -> const value_type&
  {
    assert(index < m_size);
    return m_data[index];
  }

  [[nodiscard]] constexpr auto begin() noexcept -> iterator
  {
    return m_data.data();
  }

  [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator
  {
    return m_data.data();
  }

  [[nodiscard]] constexpr auto end() noexcept -> iterator
  {
    return begin() + size();
  }

  [[nodiscard]] constexpr auto end() const noexcept -> const_iterator
  {
    return begin() + size();
  }

  /**
   * \brief Returns the maximum capacity of the vector.
   *
   * \return the capacity of the vector.
   */
  [[nodiscard]] constexpr auto capacity() const noexcept -> size_type
  {
    return Capacity;
  }

  /**
   * \brief Returns the number of elements in the vector.
   *
   * \return the current amount of elements in the vector.
   */
  [[nodiscard]] constexpr auto size() const noexcept -> size_type
  {
    return m_size;
  }

  /**
   * \brief Indicates whether or not the vector is empty.
   *
   * \return `true` if the vector is empty; `false` otherwise.
   */
  [[nodiscard]] constexpr auto empty() const noexcept -> bool
  {
    return m_size == 0;
  }

  void serialize(auto& archive)
  {
    archive(m_data, m_size);
  }

 private:
  std::array<value_type, Capacity> m_data{};
  size_type m_size{0};
};

template <typename T, typename... Rest>
static_vector(T, Rest...) -> static_vector<T, 1u + sizeof...(Rest)>;

}  // namespace wanderer
