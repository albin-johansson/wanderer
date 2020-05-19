#pragma once
#include "action.h"
#include "input.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class KeyBind {
 public:
  enum class Trigger { OnPress, OnRelease };

  KeyBind(UniquePtr<IAction>&& action, ctn::Key key, Trigger trigger);

  void update(const Input& input) noexcept;

 private:
  UniquePtr<IAction> m_action;
  ctn::Key m_key;
  Trigger m_trigger;
};

WANDERER_SERIALIZE_ENUM(KeyBind::Trigger,
                        {{KeyBind::Trigger::OnPress, "OnPress"},
                         {KeyBind::Trigger::OnRelease, "OnRelease"}})

}  // namespace albinjohansson::wanderer
