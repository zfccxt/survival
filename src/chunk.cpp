#include "chunk.hpp"

Chunk::Chunk(std::shared_ptr<cl::Context>& context, std::shared_ptr<cl::Shader>& shader, int x, int y) {
  cl::MeshCreateInfo mesh_info;
  mesh_info.vertex_input_layout = shader->GetInputLayout();
  mesh_info.vertices = {
  //  x      y     z   
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
  };
  mesh_info.indices = {
    0, 1, 2, 
    1, 3, 2, 
  };
  mesh_ = context->CreateMesh(mesh_info);
}

void Chunk::Draw() {
  mesh_->Draw();
}
