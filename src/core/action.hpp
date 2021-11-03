#pragma once

namespace wanderer {

/// \brief Provides identifiers for all of the possible menu actions.
/// \ingroup core
enum class Action
{
  None,
  GotoInGame,
  GotoHome,
  GotoSettings,
  GotoSaves,
  GotoControls,
  QuickSave,
  LoadGame,
  DeleteGame,
  ChangeSavePreview,
  IncrementSavesButtonGroupPage,
  DecrementSavesButtonGroupPage,
  Quit,
  ToggleFullscreen,
  ToggleIntegerScaling
};

}  // namespace wanderer
