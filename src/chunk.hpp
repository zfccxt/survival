#pragma once

#include <calcium.hpp>

#include "floor_tile.hpp"

class Chunk {
public:
  Chunk(cl::Context* context, std::shared_ptr<cl::Shader>& shader, int x, int z);

  void Draw();

  void LoadChunkData();
  void LoadMesh(cl::Context* context, std::shared_ptr<cl::Shader>& shader);

private:
  const static int kChunkSize = 16;

  std::shared_ptr<cl::Mesh> mesh_;

  FloorTile floor_tiles_[kChunkSize][kChunkSize];
  float x_, z_;
};
