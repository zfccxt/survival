#include "level.hpp"

constexpr int kDrawDistance = 1;

Level::Level(std::shared_ptr<cl::Context>& context) : context_(context) {
  chunk_shader_ = context->CreateShader("res/shaders/chunk_shader.vert.spv", "res/shaders/chunk_shader.frag.spv");

  cl::TextureArrayCreateInfo floor_texture_array_info;
  floor_texture_array_info.AddFile("res/textures/floors/floor_planks.png");
  floor_texture_array_info.AddFile("res/textures/floors/floor_grass.png");
  floor_texture_array_ = context->CreateTextureArray(floor_texture_array_info);
  chunk_shader_->BindTextureArray("u_floor_texture_array", floor_texture_array_);

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
