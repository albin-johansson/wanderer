#pragma once
#include "action.h"
#include "wanderer_core.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class QuitAction : public IAction {
 public:
  explicit QuitAction(Weak<IWandererCore> core) noexcept;

  ~QuitAction() noexcept override = default;

  void execute() noexcept override;

 private:
  Weak<IWandererCore> m_core;
};

}  // namespace albinjohansson::wanderer
