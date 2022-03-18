#include "chunk.hpp"

#include <random>

#include "tree_mesh.hpp"

std::default_random_engine generator;
std::normal_distribution<float> gaussian(0.0f, 0.5f);

Chunk::Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& chunk_shader, int x, int z)
    : x_(x), z_(z), context_(context), chunk_shader_(chunk_shader) {
  LoadChunkData();
  LoadMesh();
}

void Chunk::LoadChunkData() {
  // TODO: Load from file instead of generating data
  // This is all garbage test code
  for (size_t x = 0; x < kChunkSize; ++x) {
    for (size_t z = 0; z < kChunkSize; ++z) {
      for (size_t y = 0; y < kChunkHeightLimit; ++y) {

        if (y == 0) {
          tiles_[x][z][y].floor = (rand() % 100 > 50) ? TileObject::kFloorWoodPlanks : TileObject::kFloorGrass;
          tiles_[x][z][y].prop  = (rand() % 100 > 95) ? TileObject::kPropTree : TileObject::kNone;
        }
      }
    }
  }
}

void LoadFloorMesh(TileObject floor_tile, Chunk::MeshLoadInfo& mesh) {
  if (floor_tile == TileObject::kNone) {
    return;
  }

  float tex_index = TextureArrayIndex(floor_tile);
  
  std::vector<float> vertices = {
  // Top Face
  //            x           y                    z        u     v       w
    mesh.x_offs + 0.0f, mesh.y_offs, mesh.z_offs + 0.0f, 0.0f, 0.0f, tex_index,
    mesh.x_offs + 1.0f, mesh.y_offs, mesh.z_offs + 0.0f, 1.0f, 0.0f, tex_index,
    mesh.x_offs + 0.0f, mesh.y_offs, mesh.z_offs + 1.0f, 0.0f, 1.0f, tex_index,
    mesh.x_offs + 1.0f, mesh.y_offs, mesh.z_offs + 1.0f, 1.0f, 1.0f, tex_index,
  
  // Bottom Face
    mesh.x_offs + 0.0f, mesh.y_offs, mesh.z_offs + 1.0f, 0.0f, 0.0f, tex_index,
    mesh.x_offs + 1.0f, mesh.y_offs, mesh.z_offs + 1.0f, 1.0f, 0.0f, tex_index,
    mesh.x_offs + 0.0f, mesh.y_offs, mesh.z_offs + 0.0f, 0.0f, 1.0f, tex_index,
    mesh.x_offs + 1.0f, mesh.y_offs, mesh.z_offs + 0.0f, 1.0f, 1.0f, tex_index
  };
  mesh.mesh_info.vertices.insert(mesh.mesh_info.vertices.end(), vertices.begin(), vertices.end());
  
  std::vector<uint32_t> indices = {
    mesh.current_index + 0, mesh.current_index + 1, mesh.current_index + 2,
    mesh.current_index + 1, mesh.current_index + 3, mesh.current_index + 2,
    mesh.current_index + 4, mesh.current_index + 5, mesh.current_index + 6,
    mesh.current_index + 5, mesh.current_index + 7, mesh.current_index + 6,
  };
  mesh.mesh_info.indices.insert(mesh.mesh_info.indices.end(), indices.begin(), indices.end());
  
  mesh.current_index += vertices.size() / Chunk::kVertexSize;
}

void LoadPropMesh(TileObject prop, Chunk::MeshLoadInfo& mesh) {
  switch (prop) {
    // TODO: load height and x and z offs from file
    case TileObject::kPropTree: LoadTreeMesh(5.0f + gaussian(generator) * 2.5f, gaussian(generator) * 0.4f, gaussian(generator) * 0.4f, mesh);
  }
}

void Chunk::LoadMesh() {
  MeshLoadInfo mesh;
  mesh.mesh_info.vertex_input_layout = chunk_shader_->GetInputLayout();
 
  // Create floors
  for (size_t x = 0; x < kChunkSize; ++x) {
    mesh.x_offs = x + x_ * kChunkSize;
    for (size_t z = 0; z < kChunkSize; ++z) {
      mesh.z_offs = z + z_ * kChunkSize;
      for (size_t y = 0; y < kChunkHeightLimit; ++y) {
        mesh.y_offs = y * -kCeilingHeight;
        
        LoadFloorMesh(tiles_[x][z][y].floor, mesh);
        LoadPropMesh (tiles_[x][z][y].prop,  mesh);
      }
    }
  }

  mesh_ = context_->CreateMesh(mesh.mesh_info);
}

void Chunk::Draw() {
  mesh_->Draw();
}
