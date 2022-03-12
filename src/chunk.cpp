#include "chunk.hpp"

Chunk::Chunk(cl::Context* context, std::shared_ptr<cl::Shader>& shader, int x, int z) : x_(x), z_(z) {
  LoadChunkData();
  LoadMesh(context, shader);
}

void Chunk::LoadChunkData() {
  for (size_t x = 0; x < kChunkSize; ++x) {
    for (size_t z = 0; z < kChunkSize; ++z) {
      floor_tiles_[x][z] = FloorTile::kWoodPlanks;
    }
  }
}

void Chunk::LoadMesh(cl::Context* context, std::shared_ptr<cl::Shader>& shader) {
  cl::MeshCreateInfo mesh_info;
  mesh_info.vertex_input_layout = shader->GetInputLayout();

  uint32_t current_index = 0;

  // Create floors
  for (size_t x = 0; x < kChunkSize; ++x) {
    float x_offs = x + x_ * kChunkSize;
    for (size_t z = 0; z < kChunkSize; ++z) {
      float z_offs = z + z_ * kChunkSize;

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

  mesh_ = context->CreateMesh(mesh_info);
}

void Chunk::Draw() {
  mesh_->Draw();
}
