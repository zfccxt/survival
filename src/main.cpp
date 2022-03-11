#include <calcium.hpp>

#include "level.hpp"

int main() {
  auto context = cl::Context::CreateContext();
  
  auto window = context->CreateWindow();

   Level level(context);

  while (window->IsOpen()) {
    window->PollEvents();

    context->BeginFrame();
    level.Draw();
    context->EndFrame();
  }
}
