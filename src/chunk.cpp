#include "chunk.hpp"

#include <random>

Chunk::Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& chunk_shader, std::shared_ptr<cl::Texture>& floor_texture, int x, int z)
    : x_(x), z_(z), context_(context), chunk_shader_(chunk_shader), floor_texture_(floor_texture) {
  LoadChunkData();
  LoadMesh();
}

void Chunk::LoadChunkData() {
  for (size_t x = 0; x < kChunkSize; ++x) {
    for (size_t z = 0; z < kChunkSize; ++z) {
      floor_tiles_[x][z] = (rand() % 10 > 5) ? FloorTile::kWoodPlanks : FloorTile::kGrass;
    }
  }
}

void Chunk::LoadMesh() {
  cl::MeshCreateInfo mesh_info;
  mesh_info.vertex_input_layout = chunk_shader_->GetInputLayout();

  uint32_t current_index = 0;
 
  // Create floors
  for (size_t x = 0; x < kChunkSize; ++x) {
    float x_offs = x + x_ * kChunkSize;
    for (size_t z = 0; z < kChunkSize; ++z) {
      float z_offs = z + z_ * kChunkSize;

      FloorTile current_floor_tile = floor_tiles_[x][z];
      if (current_floor_tile == FloorTile::kNone) {
        continue;
      }

      std::vector<float> vertices = {
      //       x        y           z        u     v
        x_offs + 0.0f, 0.0f, z_offs + 0.0f, 0.0f, 0.0f,
        x_offs + 1.0f, 0.0f, z_offs + 0.0f, 1.0f, 0.0f,
        x_offs + 0.0f, 0.0f, z_offs + 1.0f, 0.0f, 1.0f,
        x_offs + 1.0f, 0.0f, z_offs + 1.0f, 1.0f, 1.0f,
      };
      mesh_info.vertices.insert(mesh_info.vertices.end(), vertices.begin(), vertices.end());

      std::vector<uint32_t> indices = {
        current_index + 0, current_index + 1, current_index + 2, 
        current_index + 1, current_index + 3, current_index + 2, 
      };
      mesh_info.indices.insert(mesh_info.indices.end(), indices.begin(), indices.end());

      current_index += 4;
    }
  }

  mesh_ = context_->CreateMesh(mesh_info);
}

void Chunk::Draw() {
  mesh_->Draw();
}
