#include <calcium.hpp>

#include "camera.hpp"
#include "level.hpp"

int main() {
  auto context = cl::Context::CreateContext();
  
  auto window = context->CreateWindow();
  Camera camera(window);
  auto recalc_projection = [&](){ camera.CalculateProjection(window->GetAspectRatio()); };
  window->SetResizeCallback(recalc_projection);
  recalc_projection();

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
