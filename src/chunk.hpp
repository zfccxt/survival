#pragma once

#include <calcium.hpp>

class Chunk {
public:
  Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& shader, int x, int y);

  void Draw();

private:
  std::shared_ptr<cl::Mesh> mesh_;
};
