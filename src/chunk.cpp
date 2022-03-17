#include "chunk.hpp"

#include <random>

Chunk::Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& chunk_shader, int x, int z)
    : x_(x), z_(z), context_(context), chunk_shader_(chunk_shader) {
  LoadChunkData();
  LoadMesh();
}

void Chunk::LoadChunkData() {
  // TODO: Load from file instead of generating data
  for (size_t x = 0; x < kChunkSize; ++x) {
    for (size_t z = 0; z < kChunkSize; ++z) {
      for (size_t y = 0; y < kChunkHeightLimit; ++y) {

        if (y == 0) {
          tiles_[x][z][y].floor = (rand() % 10 > 5) ? FloorTile::kWoodPlanks : FloorTile::kGrass;
        }
        else {
          tiles_[x][z][y].floor = FloorTile::kNone;
        }

      }
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
      for (size_t y = 0; y < kChunkHeightLimit; ++y) {
        float y_offs = y * -2.35f; // Avg ceiling height is approx 2.35 metres

        FloorTile current_floor_tile = tiles_[x][z][y].floor;
        if (current_floor_tile == FloorTile::kNone) {
          continue;
        }
        
        std::vector<float> vertices = {
        // Top Face
        //       x          y           z        u     v                   w
          x_offs + 0.0f, y_offs, z_offs + 0.0f, 0.0f, 0.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),
          x_offs + 1.0f, y_offs, z_offs + 0.0f, 1.0f, 0.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),
          x_offs + 0.0f, y_offs, z_offs + 1.0f, 0.0f, 1.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),
          x_offs + 1.0f, y_offs, z_offs + 1.0f, 1.0f, 1.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),

        // Bottom Face
          x_offs + 0.0f, y_offs, z_offs + 1.0f, 0.0f, 0.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),
          x_offs + 1.0f, y_offs, z_offs + 1.0f, 1.0f, 0.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),
          x_offs + 0.0f, y_offs, z_offs + 0.0f, 0.0f, 1.0f, FloorTileProps::TextureArrayIndex(current_floor_tile),
          x_offs + 1.0f, y_offs, z_offs + 0.0f, 1.0f, 1.0f, FloorTileProps::TextureArrayIndex(current_floor_tile)
        };
        mesh_info.vertices.insert(mesh_info.vertices.end(), vertices.begin(), vertices.end());
        
        std::vector<uint32_t> indices = {
          current_index + 0, current_index + 1, current_index + 2, 
          current_index + 1, current_index + 3, current_index + 2, 
          current_index + 4, current_index + 5, current_index + 6, 
          current_index + 5, current_index + 7, current_index + 6, 
        };
        mesh_info.indices.insert(mesh_info.indices.end(), indices.begin(), indices.end());
        
        current_index += 8;
      }
    }
  }

  mesh_ = context_->CreateMesh(mesh_info);
}

void Chunk::Draw() {
  mesh_->Draw();
}
