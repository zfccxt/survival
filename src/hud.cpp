#include "hud.hpp"

#include <clx_imgui.hpp>

namespace Hud {

void DrawHudWindows() {
  clx::imgui::Begin();

  ImGui::SetNextWindowPos({ImGui::GetMainViewport()->Size.x - 400, 0}, ImGuiCond_Once);
  ImGui::SetNextWindowSize({ 400, 400 }, ImGuiCond_Once);
  ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);
  ImGui::Begin("Inventory");
  ImGui::End();

  clx::imgui::End();
}

}
