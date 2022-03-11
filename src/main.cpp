#include <calcium.hpp>

#include "camera.hpp"
#include "level.hpp"

int main() {
  auto context = cl::Context::CreateContext();
  
  auto window = context->CreateWindow();

  Camera camera(window);
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
