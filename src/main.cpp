#include <calcium.hpp>

int main() {
  auto context = cl::Context::CreateContext();
  
  auto window = context->CreateWindow();

  while (window->IsOpen()) {
    window->PollEvents();

    context->BeginFrame();
    context->EndFrame();
  }
}
