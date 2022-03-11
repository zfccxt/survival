#pragma once

#include <calcium.hpp>

class Chunk {
public:
  Chunk(std::shared_ptr<cl::Context>& context, int x, int y);
  ~Chunk();

  void Draw();

private:
  std::shared_ptr<cl::Mesh> mesh_;
};
