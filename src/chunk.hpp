#pragma once

#include <calcium.hpp>

#include "floor_tile.hpp"

class Chunk {
public:
  Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& chunk_shader, std::shared_ptr<cl::Texture>& floor_texture, int x, int z);

  void Draw();

  void LoadChunkData();
  void LoadMesh();


private:
  std::shared_ptr<cl::Context> context_;
  std::shared_ptr<cl::Shader> chunk_shader_;
  std::shared_ptr<cl::Texture> floor_texture_;

private:
  const static int kChunkSize = 16;

private:
  std::shared_ptr<cl::Mesh> mesh_;

  FloorTile floor_tiles_[kChunkSize][kChunkSize];
  float x_, z_;
};
