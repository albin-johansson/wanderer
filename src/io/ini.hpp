#pragma once

#include <algorithm>    // find_if
#include <cstddef>      // size_t
#include <functional>   // less
#include <istream>      // istream
#include <locale>       // locale, isspace
#include <map>          // map
#include <optional>     // optional
#include <stdexcept>    // invalid_argument
#include <string>       // string, getline, stoi, stol, stof, stod
#include <string_view>  // string_view
#include <type_traits>  // is_same_v

namespace wanderer {

template <typename Character>
struct ini_format final
{
  using value_type = Character;
  value_type sectionStart = '[';
  value_type sectionEnd = ']';
  value_type assign = '=';
  value_type comment = ';';
};

template <typename Character>
class basic_ini final
{
 public:
  using character_type = Character;
  using string_type = std::basic_string<character_type>;
  using string_view_type = std::basic_string_view<character_type>;
  using section_type = std::map<string_type, string_type, std::less<>>;
  using section_map = std::map<string_type, section_type, std::less<>>;
  using format_type = ini_format<Character>;
  using size_type = std::size_t;
  using input_stream = std::basic_istream<Character>;
  using const_iterator = typename section_map::const_iterator;

  explicit basic_ini(input_stream& stream)
  {
    string_type line;
    string_type sectionName;

    line.reserve(24);
    sectionName.reserve(24);

    while (std::getline(stream, line))
    {
      trim_left(line);
      trim_right(line);
      parse_line(sectionName, line);
    }
  }

  void clear() noexcept
  {
    m_sections.clear();
  }

  [[nodiscard]] auto at(const string_view_type section,
                        const string_view_type entry) const
      -> const string_type&
  {
    if (const auto it = m_sections.find(section); it != m_sections.end())
    {
      if (const auto it2 = it->second.find(entry); it2 != it->second.end())
      {
        return it2->second;
      }
    }

    throw std::invalid_argument{"Unknown section or section entry!"};
  }

  template <typename T>
  [[nodiscard]] auto get(const string_view_type section,
                         const string_view_type entry) const -> std::optional<T>
  {
    if (const auto it = find(section, entry))
    {
      const auto& value = (*it)->second;

      if constexpr (std::is_same_v<T, int>)
      {
        return std::stoi(value);

      } else if constexpr (std::is_same_v<T, long>)
      {
        return std::stol(value);

      } else if constexpr (std::is_same_v<T, float>)
      {
        return std::stof(value);

      } else if constexpr (std::is_same_v<T, double>)
      {
        return std::stod(value);

      } else if constexpr (std::is_same_v<T, bool>)
      {
        return value == "true" || value == "false";

      } else if constexpr (std::is_same_v<T, string_type>)
      {
        return value;
      }
    }

    return std::nullopt;
  }

  [[nodiscard]] auto contains(const string_view_type section) const -> bool
  {
    return m_sections.find(section) != m_sections.end();
  }

  [[nodiscard]] auto section_count() const noexcept -> size_type
  {
    return m_sections.size();
  }

  [[nodiscard]] auto begin() const noexcept -> const_iterator
  {
    return m_sections.begin();
  }

  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return m_sections.end();
  }

  [[nodiscard]] auto errors() const -> const std::vector<string_type>&
  {
    return m_errors;
  }

  explicit operator bool() const noexcept
  {
    return m_errors.empty();
  }

 private:
  section_map m_sections;
  format_type m_format;
  mutable std::vector<string_type> m_errors;

  [[nodiscard]] auto parse_section_name(const string_type& line) const
      -> std::optional<string_type>
  {
    if (is_section_end(line.back()))
    {
      return line.substr(1, line.length() - 2);
    } else
    {
      m_errors.push_back(line);
      return std::nullopt;
    }
  }

  void parse_line(string_type& sectionName, const string_type& line)
  {
    if (line.empty())
    {
      return;
    }

    const auto& character = line.front();

    if (is_comment(character))
    {
      return;
    }

    if (is_section_start(character))
    {
      if (const auto name = parse_section_name(line))
      {
        sectionName = *name;
      }
    } else if (parse_variable(line, sectionName))
    {
    } else
    {
      m_errors.push_back(line);
    }
  }

  auto parse_variable(const string_type& line, const string_type& sectionName)
      -> bool
  {
    const auto assignmentPos =
        std::find_if(line.begin(),
                     line.end(),
                     [this](const character_type character) {
                       return is_assignment(character);
                     });

    string_type variable{line.begin(), assignmentPos};
    string_type value{assignmentPos + 1, line.end()};

    trim_right(variable);
    trim_left(variable);

    auto& section = m_sections[sectionName];
    if (section.find(variable) == section.end())
    {
      section.try_emplace(variable, value);
      return true;
    } else
    {
      m_errors.push_back(line);
      return false;
    }
  }

  [[nodiscard]] auto find(const string_view_type section,
                          const string_view_type entry) const
      -> std::optional<typename section_type::const_iterator>
  {
    if (const auto it = m_sections.find(section); it != m_sections.end())
    {
      const auto& map = it->second;
      if (const auto it2 = map.find(entry); it2 != map.end())
      {
        return it2;
      }
    }

    return std::nullopt;
  }

  [[nodiscard]] auto is_comment(const character_type ch) const -> bool
  {
    return ch == m_format.comment;
  }

  [[nodiscard]] auto is_assignment(const character_type ch) const -> bool
  {
    return ch == m_format.assign;
  }

  [[nodiscard]] auto is_section_start(const character_type ch) const -> bool
  {
    return ch == m_format.sectionStart;
  }

  [[nodiscard]] auto is_section_end(const character_type ch) const -> bool
  {
    return ch == m_format.sectionEnd;
  }

  static void trim_left(string_type& str)
  {
    const auto it = find_first_non_space(str.begin(), str.end());
    str.erase(str.begin(), it);
  }

  static void trim_right(string_type& str)
  {
    const auto it = find_first_non_space(str.rbegin(), str.rend());
    str.erase(it.base(), str.end());
  }

  template <typename T>
  [[nodiscard]] static auto find_first_non_space(const T begin, const T end)
  {
    return std::find_if(begin, end, [](const character_type ch) {
      return !std::isspace(ch, std::locale::classic());
    });
  }
};

using ini_file = basic_ini<char>;

}  // namespace wanderer
