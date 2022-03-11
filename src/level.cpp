#include "level.hpp"

Level::Level(std::shared_ptr<cl::Context>& context) {
  chunk_shader_ = context->CreateShader("res/shaders/chunk_shader.vert.spv", "res/shaders/chunk_shader.frag.spv");

  chunk_ = std::make_unique<Chunk>(context, chunk_shader_, 0, 0);
}

void Level::Draw() {
  chunk_shader_->Bind();

  chunk_->Draw();
}

void Level::SetCameraPos(Camera& camera) {
  camera.UploadTo(chunk_shader_);
}
