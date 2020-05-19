#pragma once
#include "action.h"
#include "wanderer_core.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class QuitAction : public IAction {
 public:
  explicit QuitAction(WeakPtr<IWandererCore> core) noexcept;

  ~QuitAction() noexcept override = default;

  void execute() noexcept override;

 private:
  WeakPtr<IWandererCore> m_core;
};

}  // namespace wanderer
