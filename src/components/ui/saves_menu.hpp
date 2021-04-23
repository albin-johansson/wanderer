#pragma once

#include <centurion.hpp>  // surface
#include <string>         // string
#include <vector>         // vector

#include "components/ui/button.hpp"
#include "components/ui/label.hpp"
#include "components/ui/lazy_texture.hpp"
#include "core/aliases/entity_type.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct saves_menu_t;
struct saves_menu_entry_t;
}  // namespace detail

struct saves_menu_entry final
{
  using entity = entity_type<detail::saves_menu_entry_t>;

  std::string name;      ///< The name of the save file.
  cen::surface preview;  ///< The preview image for the save.
  int dataVersion;       ///< The serialized data version used by the save.

  // TODO total play time
};

struct associated_saves_entry final
{
  saves_menu_entry::entity entry{null<saves_menu_entry>()};
};

struct saves_menu final
{
  using entity = entity_type<detail::saves_menu_t>;

  std::vector<saves_menu_entry::entity> entries;

  button::entity decrementButton{null<button>()};
  button::entity incrementButton{null<button>()};
  button::entity deleteButton{null<button>()};
  button::entity loadButton{null<button>()};

  label::entity titleLabel{null<label>()};
  label::entity timeLabel{null<label>()};
  label::entity dataVersionLabel{null<label>()};

  lazy_texture::entity previewTexture{null<lazy_texture>()};
};

}  // namespace wanderer::comp
