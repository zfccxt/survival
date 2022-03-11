#pragma once

#include <calcium.hpp>

#include "camera.hpp"
#include "chunk.hpp"

class Level {
public:
  Level(std::shared_ptr<cl::Context>& context);

  void Draw();
  void SetCameraPos(Camera& camera);

private:
  std::shared_ptr<cl::Shader> chunk_shader_;

  std::unique_ptr<Chunk> chunk_;
};
