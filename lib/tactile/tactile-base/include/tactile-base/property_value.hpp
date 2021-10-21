#pragma once

#include <filesystem>  // path
#include <string>      // string
#include <variant>     // variant, monostate, get, get_if, holds_alternative

#include <centurion.hpp>  // color

#include "property_type.hpp"
#include "tactile_std.hpp"

namespace Tactile {

/// \addtogroup core
/// \{

// clang-format off

template <typename T>
concept IsPropertyType = std::same_as<T, std::string> ||
                         std::same_as<T, int> ||
                         std::same_as<T, float> ||
                         std::same_as<T, bool> ||
                         std::same_as<T, cen::color> ||
                         std::same_as<T, std::filesystem::path> ||
                         std::same_as<T, ObjectRef>;

// clang-format on

class PropertyValue final
{
 public:
  using string_type = std::string;
  using integer_type = int;
  using float_type = float;
  using color_type = cen::color;
  using file_type = std::filesystem::path;

  using value_type = std::variant<std::monostate,
                                  string_type,
                                  integer_type,
                                  float_type,
                                  bool,
                                  color_type,
                                  file_type,
                                  ObjectRef>;

  /// Creates a property with no value.
  PropertyValue() = default;

  /**
   * \brief Creates a property.
   *
   * \tparam T the type of the property value.
   *
   * \param value the value of the property.
   */
  template <IsPropertyType T>
  /*implicit*/ PropertyValue(const T& value)
  {
    mValue.emplace<T>(value);
  }

  /**
   * \brief Resets the state of the property.
   *
   * \post `HasValue()` will return `false` after this function is invoked.
   */
  void Reset()
  {
    mValue.emplace<std::monostate>();
  }

  void ResetToDefault(PropertyType type)
  {
    if (type == PropertyType::Integer) {
      SetValue<integer_type>(0);
    }
    else if (type == PropertyType::Floating) {
      SetValue<float_type>(0);
    }
    else if (type == PropertyType::Boolean) {
      SetValue<bool>(false);
    }
    else if (type == PropertyType::String) {
      SetValue<string_type>(string_type{});
    }
    else if (type == PropertyType::Color) {
      SetValue<color_type>(cen::colors::black);
    }
    else if (type == PropertyType::Object) {
      SetValue<ObjectRef>(ObjectRef{});
    }
    else if (type == PropertyType::File) {
      SetValue<file_type>(file_type{});
    }
  }

  /**
   * \brief Sets the value stored in the property.
   *
   * \tparam T the type of the value.
   *
   * \param value the new value of the property.
   */
  template <IsPropertyType T>
  void SetValue(const T& value)
  {
    mValue.emplace<T>(value);
  }

  /**
   * \brief Indicates whether or not the property holds a value.
   *
   * \return `true` if the property holds a value; `false` otherwise.
   */
  [[nodiscard]] auto HasValue() const noexcept -> bool
  {
    return !std::holds_alternative<std::monostate>(mValue);
  }

  /**
   * \brief Returns the stored string value.
   *
   * \note This function throws if the stored value isn't a string.
   *
   * \return the stored color.
   */
  [[nodiscard]] auto AsString() const -> const string_type&
  {
    return As<string_type>();
  }

  /**
   * \brief Returns the stored integer value.
   *
   * \note This function throws if the stored value isn't an integer.
   *
   * \return the stored integer.
   */
  [[nodiscard]] auto AsInt() const -> integer_type
  {
    return As<integer_type>();
  }

  /**
   * \brief Returns the stored float value.
   *
   * \note This function throws if the stored value isn't a float.
   *
   * \return the stored floating-point value.
   */
  [[nodiscard]] auto AsFloat() const -> float_type
  {
    return As<float_type>();
  }

  /**
   * \brief Returns the stored boolean value.
   *
   * \note This function throws if the stored value isn't a boolean.
   *
   * \return the stored boolean value.
   */
  [[nodiscard]] auto AsBool() const -> bool
  {
    return As<bool>();
  }

  /**
   * \brief Returns the stored file path value.
   *
   * \note This function throws if the stored value isn't a file path.
   *
   * \return the stored file path value.
   */
  [[nodiscard]] auto AsFile() const -> const file_type&
  {
    return As<file_type>();
  }

  /**
   * \brief Returns the stored object ID value.
   *
   * \note This function throws if the stored value isn't an object ID.
   *
   * \return the stored object ID value.
   */
  [[nodiscard]] auto AsObject() const -> ObjectRef
  {
    return As<ObjectRef>();
  }

  /**
   * \brief Returns the stored color value.
   *
   * \note This function throws if the stored value isn't a color.
   *
   * \return the stored color value.
   */
  [[nodiscard]] auto AsColor() const -> const color_type&
  {
    return As<color_type>();
  }

  [[nodiscard]] auto TryAsString() const noexcept -> const string_type*
  {
    return TryAs<string_type>();
  }

  [[nodiscard]] auto TryAsInt() const noexcept -> const integer_type*
  {
    return TryAs<integer_type>();
  }

  [[nodiscard]] auto TryAsFloat() const noexcept -> const float_type*
  {
    return TryAs<float_type>();
  }

  [[nodiscard]] auto TryAsBool() const noexcept -> const bool*
  {
    return TryAs<bool>();
  }

  [[nodiscard]] auto TryAsFile() const noexcept -> const file_type*
  {
    return TryAs<file_type>();
  }

  [[nodiscard]] auto TryAsObject() const noexcept -> const ObjectRef*
  {
    return TryAs<ObjectRef>();
  }

  [[nodiscard]] auto TryAsColor() const noexcept -> const color_type*
  {
    return TryAs<color_type>();
  }

  /**
   * \brief Indicates whether or not the stored value is a string.
   *
   * \return `true` if the stored value is a string; `false` otherwise.
   */
  [[nodiscard]] auto IsString() const noexcept -> bool
  {
    return GetType() == PropertyType::String;
  }

  /**
   * \brief Indicates whether or not the stored value is an integer.
   *
   * \return `true` if the stored value is an integer; `false` otherwise.
   */
  [[nodiscard]] auto IsInt() const noexcept -> bool
  {
    return GetType() == PropertyType::Integer;
  }

  /**
   * \brief Indicates whether or not the stored value is a floating-point
   * number.
   *
   * \return `true` if the stored value is a floating-point number; `false`
   * otherwise.
   */
  [[nodiscard]] auto IsFloat() const noexcept -> bool
  {
    return GetType() == PropertyType::Floating;
  }

  /**
   * \brief Indicates whether or not the stored value is a boolean.
   *
   * \return `true` if the stored value is a boolean; `false` otherwise.
   */
  [[nodiscard]] auto IsBool() const noexcept -> bool
  {
    return GetType() == PropertyType::Boolean;
  }

  /**
   * \brief Indicates whether or not the stored value is a file path.
   *
   * \return `true` if the stored value is a file path; `false` otherwise.
   */
  [[nodiscard]] auto IsFile() const noexcept -> bool
  {
    return GetType() == PropertyType::File;
  }

  /**
   * \brief Indicates whether or not the stored value is an object ID.
   *
   * \return `true` if the stored value is an object ID; `false` otherwise.
   */
  [[nodiscard]] auto IsObject() const noexcept -> bool
  {
    return GetType() == PropertyType::Object;
  }

  /**
   * \brief Indicates whether or not the stored value is a color.
   *
   * \return `true` if the stored value is a color; `false` otherwise.
   */
  [[nodiscard]] auto IsColor() const noexcept -> bool
  {
    return GetType() == PropertyType::Color;
  }

  /**
   * \brief Returns the type of the stored value.
   *
   * \return the type of the stored value; `nothing` if there is no value.
   */
  [[nodiscard]] auto GetType() const -> Maybe<PropertyType>
  {
    if (Is<integer_type>()) {
      return PropertyType::Integer;
    }
    else if (Is<float_type>()) {
      return PropertyType::Floating;
    }
    else if (Is<string_type>()) {
      return PropertyType::String;
    }
    else if (Is<bool>()) {
      return PropertyType::Boolean;
    }
    else if (Is<file_type>()) {
      return PropertyType::File;
    }
    else if (Is<ObjectRef>()) {
      return PropertyType::Object;
    }
    else if (Is<color_type>()) {
      return PropertyType::Color;
    }
    else {
      return nothing;
    }
  }

 private:
  value_type mValue;

  template <IsPropertyType T>
  [[nodiscard]] auto Is() const noexcept -> bool
  {
    return std::holds_alternative<T>(mValue);
  }

  template <IsPropertyType T>
  [[nodiscard]] auto As() const -> const T&
  {
    return std::get<T>(mValue);
  }

  template <IsPropertyType T>
  [[nodiscard]] auto TryAs() const noexcept -> const T*
  {
    return std::get_if<T>(&mValue);
  }
};

/// \} End of group core

}  // namespace Tactile
