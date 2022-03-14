#include <calcium.hpp>

#include "camera.hpp"
#include "level.hpp"

int main() {
  auto context = cl::Context::CreateContext(cl::Backend::kVulkan);
  
  auto window = context->CreateWindow();
  window->SetKeyPressCallback(cl::KeyCode::kEscape, [&]() { window->Close(); });

  Camera camera(window);
  camera.SetPosition(0.0f, 1.76f, 0.0f);
  Level level(context);

  while (window->IsOpen()) {
    window->PollEvents();
    
    camera.FreeControl(window);
    level.SetCameraPos(camera);

    context->BeginFrame();
    level.Draw();
    context->EndFrame();
  }
}
