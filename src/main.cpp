#include <calcium.hpp>

#include "chunk.hpp"

int main() {
  auto context = cl::Context::CreateContext();
  
  auto window = context->CreateWindow();

  Chunk chunk(context, 0, 0);

  while (window->IsOpen()) {
    window->PollEvents();

    context->BeginFrame();
    chunk.Draw();
    context->EndFrame();
  }
}
