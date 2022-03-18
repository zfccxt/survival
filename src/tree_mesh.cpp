#include "tree_mesh.hpp"

// TODO: Neither of these are needed
#include <random>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

constexpr float kMinBranchHeight = 0.5f;
constexpr float kBranchDensity = 7.0f; // Avg number of branches per metre tree height

void LoadTreeBranchMesh(float rot, float tree_height, float y_offs, float x_offs, float z_offs, Chunk::MeshLoadInfo& mesh) {
  float tex_index = TextureArrayIndex(TileObject::kPropTree, TileObjectMeshPart::kTreeTrunk);
  float ratio = 1.0f - (-y_offs / tree_height);
  float length = ratio * tree_height * 0.4f;
  float thickness = ratio * 0.1f;

  glm::vec4 tip = glm::rotateY(glm::vec4(0.0f, 0.0f, length, 1.0f), rot);
  glm::vec4 ul  = glm::rotateY(glm::vec4(thickness, 0.0f, 0.0f, 1.0f), rot);
  glm::vec4 ur  = glm::rotateY(glm::vec4(-thickness, 0.0f, 0.0f, 1.0f), rot);

  std::vector<float> vertices = {
  //            x                                    y                            z                         u    v       w
    mesh.x_offs + x_offs + 0.5f + tip.x, mesh.y_offs + y_offs,        mesh.z_offs + z_offs + 0.5f + tip.z, 0.0f, 0.0f, tex_index, // 0 - tip
    mesh.x_offs + x_offs + 0.5f + ul.x,  mesh.y_offs + y_offs + 0.1f, mesh.z_offs + z_offs + 0.5f + ul.z,  0.0f, 0.0f, tex_index, // 1 - base ul
    mesh.x_offs + x_offs + 0.5f + ur.x,  mesh.y_offs + y_offs + 0.1f, mesh.z_offs + z_offs + 0.5f + ur.z,  0.0f, 0.0f, tex_index, // 2 - base ur
    mesh.x_offs + x_offs + 0.5f,         mesh.y_offs + y_offs + 0.2f, mesh.z_offs + z_offs + 0.5f,         0.0f, 0.0f, tex_index, // 3 - base bottom
  };
  mesh.mesh_info.vertices.insert(mesh.mesh_info.vertices.end(), vertices.begin(), vertices.end());
  
  std::vector<uint32_t> indices = {
    mesh.current_index + 0, mesh.current_index + 2, mesh.current_index + 1,
    mesh.current_index + 0, mesh.current_index + 3, mesh.current_index + 2,
    mesh.current_index + 0, mesh.current_index + 1, mesh.current_index + 3,
  };
  mesh.mesh_info.indices.insert(mesh.mesh_info.indices.end(), indices.begin(), indices.end());
  
  mesh.current_index += vertices.size() / Chunk::kVertexSize;
}

void LoadTreeMesh(float height, float x_offs, float z_offs, Chunk::MeshLoadInfo& mesh) {
  const float trunk_tex_index = TextureArrayIndex(TileObject::kPropTree, TileObjectMeshPart::kTreeTrunk);
  const float trunk_radius = height * 0.03f;

  std::vector<float> vertices = {
  // Tree trunk - a big pyramid shape
  //            x                                   y                             z                                u     v            w
    mesh.x_offs + x_offs + 0.5f - trunk_radius, mesh.y_offs,          mesh.z_offs + z_offs + 0.5f - trunk_radius, 0.0f, 0.0f, trunk_tex_index, // 0 - base sw
    mesh.x_offs + x_offs + 0.5f + trunk_radius, mesh.y_offs,          mesh.z_offs + z_offs + 0.5f - trunk_radius, 1.0f, 0.0f, trunk_tex_index, // 1 - base se
    mesh.x_offs + x_offs + 0.5f - trunk_radius, mesh.y_offs,          mesh.z_offs + z_offs + 0.5f + trunk_radius, 0.0f, 1.0f, trunk_tex_index, // 2 - base nw
    mesh.x_offs + x_offs + 0.5f + trunk_radius, mesh.y_offs,          mesh.z_offs + z_offs + 0.5f + trunk_radius, 1.0f, 1.0f, trunk_tex_index, // 3 - base ne 
    mesh.x_offs + x_offs + 0.5f,                mesh.y_offs - height, mesh.z_offs + z_offs + 0.5f,                0.5f, 0.5f, trunk_tex_index, // 4 - top
  
  };
  mesh.mesh_info.vertices.insert(mesh.mesh_info.vertices.end(), vertices.begin(), vertices.end());
  
  std::vector<uint32_t> indices = {
    mesh.current_index + 0, mesh.current_index + 1, mesh.current_index + 4, // south
    mesh.current_index + 1, mesh.current_index + 3, mesh.current_index + 4, // east
    mesh.current_index + 3, mesh.current_index + 2, mesh.current_index + 4, // north
    mesh.current_index + 2, mesh.current_index + 0, mesh.current_index + 4, // west
  };
  mesh.mesh_info.indices.insert(mesh.mesh_info.indices.end(), indices.begin(), indices.end());
  
  mesh.current_index += vertices.size() / Chunk::kVertexSize;

  if (height > 1.7f) {
    srand(mesh.x_offs + mesh.z_offs);
    int num_branches = height * kBranchDensity;
    for (int i = 0; i < num_branches; ++i) {
      // Branches are not stored - everything should be derived from tree height, which means if a tree grows it can
      // lose or gain branches seemingly at random and that's fine
      int branch_height = (rand() % 100);
      float y_offs = (branch_height / 100.0f) * height;
      if (y_offs > kMinBranchHeight) {
        float rot = (float)rand();
        LoadTreeBranchMesh(rot, height, -y_offs, x_offs, z_offs, mesh);
      }
    }
  }
}