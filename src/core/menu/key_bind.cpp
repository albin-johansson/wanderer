#include "key_bind.h"

#include "wanderer_exception.h"

namespace albinjohansson::wanderer {

KeyBind::KeyBind(UniquePtr<IAction>&& action, ctn::Key key, Trigger trigger)
    : m_action{std::move(action)}, m_key{key}, m_trigger{trigger}
{
  if (!m_action) {
    throw WandererException{"Cannot create key bind from null action!"};
  }
}

void KeyBind::update(const Input& input) noexcept
{
  switch (m_trigger) {
    case Trigger::OnPress:
      if (input.was_just_pressed(m_key.scancode())) {
        m_action->execute();
      }
      break;
    case Trigger::OnRelease:
      if (input.was_released(m_key.scancode())) {
        m_action->execute();
      }
      break;
  }
}

}  // namespace albinjohansson::wanderer
