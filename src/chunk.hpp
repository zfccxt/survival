#pragma once

#include <calcium.hpp>

#include "chunk_mesh_utils.hpp"

class Chunk {
public:
  Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& chunk_shader, int x, int z);

  void Draw();

  void LoadChunkData();
  void LoadMesh();


private:
  std::shared_ptr<cl::Context> context_;
  std::shared_ptr<cl::Shader> chunk_shader_;

private:
  const static int kChunkSize = 16;
  const static int kChunkHeightLimit = 4; // Building max stories

private:
  std::shared_ptr<cl::Mesh> mesh_;

  ChunkTile tiles_[kChunkSize][kChunkSize][kChunkHeightLimit];

  float x_, z_;
};
