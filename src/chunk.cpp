#include "chunk.hpp"

std::shared_ptr<cl::Shader> chunk_shader_;
int num_loaded_chunks_ = 0;

Chunk::Chunk(std::shared_ptr<cl::Context>& context, int x, int y) {
  if (num_loaded_chunks_ == 0) {
    chunk_shader_ = context->CreateShader("res/shaders/chunk_shader.vert.spv", "res/shaders/chunk_shader.frag.spv");
  }
  ++num_loaded_chunks_;

  cl::MeshCreateInfo mesh_info;
  mesh_info.vertex_input_layout = chunk_shader_->GetInputLayout();
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

Chunk::~Chunk() {
  --num_loaded_chunks_;
  if (num_loaded_chunks_ == 0) {
    chunk_shader_.reset();
  }
}

void Chunk::Draw() {
  chunk_shader_->Bind();
  mesh_->Draw();
}
