#include <calcium.hpp>
#include <clx_imgui.hpp>

#include "camera.hpp"
#include "level.hpp"
#include "hud.hpp"

int main() {
  cl::ContextCreateInfo context_info;
  context_info.backend = cl::Backend::kOpenGL;
  context_info.extensions = { clx::imgui::LoadExtension() };
  auto context = cl::Context::CreateContext(context_info);
  
  auto window = context->CreateWindow();
  window->SetKeyPressCallback(cl::KeyCode::kEscape, [&]() { window->Close(); });

  Camera camera(window);
  camera.SetPosition(0.0f, 1.76f, 0.0f);
  Level level(context);

  ImGui::GetIO().IniFilename = nullptr;

  while (window->IsOpen()) {
    window->PollEvents();
    
    camera.FreeControl(window);
    level.SetCameraPos(camera);

    context->BeginFrame();
    level.Draw();

    Hud::DrawHudWindows();
    context->EndFrame();
  }
}
