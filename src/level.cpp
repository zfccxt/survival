#include "level.hpp"

constexpr int kDrawDistance = 2;

Level::Level(std::shared_ptr<cl::Context>& context) : context_(context.get()) {
  chunk_shader_ = context->CreateShader("res/shaders/chunk_shader.vert.spv", "res/shaders/chunk_shader.frag.spv");

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
