#include "level.hpp"

constexpr int kDrawDistance = 3;

Level::Level(std::shared_ptr<cl::Context>& context) : context_(context) {
  chunk_shader_ = context->CreateShader("res/shaders/chunk_shader.vert.spv", "res/shaders/chunk_shader.frag.spv");

  cl::TextureArrayCreateInfo chunk_texture_array_info;
  chunk_texture_array_info.AddFile("res/textures/chunk/empty.png");
  chunk_texture_array_info.AddFile("res/textures/chunk/floor_planks.png");
  chunk_texture_array_info.AddFile("res/textures/chunk/floor_grass.png");
  chunk_texture_array_info.AddFile("res/textures/chunk/prop_tree_leaves.png");
  chunk_texture_array_info.AddFile("res/textures/chunk/prop_tree_trunk.png");
  chunk_texture_array_ = context->CreateTextureArray(chunk_texture_array_info);
  chunk_shader_->BindTextureArray("u_chunk_texture_array", chunk_texture_array_);

  for (int x = -kDrawDistance; x < kDrawDistance; ++x) {
    for (int z = -kDrawDistance; z < kDrawDistance; ++z) {
      LoadChunk(x, z);
    }
  }
}

void Level::LoadChunk(int x, int z) {
  chunk_map_.emplace(std::make_pair(x, z), std::make_unique<Chunk>(context_, chunk_shader_, x, z));
}

void Level::Draw() {
  chunk_shader_->Bind();

  for (const auto& chunk : chunk_map_) {
    chunk.second->Draw();
  }
}

void Level::SetCameraPos(Camera& camera) {
  camera.UploadTo(chunk_shader_);
}
