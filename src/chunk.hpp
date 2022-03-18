#pragma once

#include <random>

#include <calcium.hpp>

#include "chunk_mesh_utils.hpp"

class Chunk {
public:
  Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& chunk_shader, int x, int z);

  void Draw();

  void LoadChunkData();
  void LoadMesh();

public:
  constexpr static size_t kVertexSize = 6;
  constexpr static float kCeilingHeight = 2.5f; // Avg ceiling height in uk is 2.35m but that feels a little claustrophobic and this is a more "round" number
  constexpr static int kChunkSize = 16;
  constexpr static int kChunkHeightLimit = 4; // Building max stories

public:
  struct MeshLoadInfo {
    cl::MeshCreateInfo mesh_info;
    uint32_t current_index = 0;
    float x_offs = 0.0f;
    float y_offs = 0.0f;
    float z_offs = 0.0f;
  };

private:
  std::shared_ptr<cl::Context> context_;
  std::shared_ptr<cl::Shader> chunk_shader_;

private:
  std::shared_ptr<cl::Mesh> mesh_;

  ChunkTile tiles_[kChunkSize][kChunkSize][kChunkHeightLimit];

  float x_, z_;
};
