#pragma once

#include <map>

#include <calcium.hpp>

#include "camera.hpp"
#include "chunk.hpp"

class Level {
public:
  Level(std::shared_ptr<cl::Context>& context);

  void Draw();
  void SetCameraPos(Camera& camera);

private:
  void LoadChunk(int x, int z);

private:
  cl::Context* context_;
  std::shared_ptr<cl::Shader> chunk_shader_;

  std::map<std::pair<int, int>, std::unique_ptr<Chunk>> chunk_map_;
};
