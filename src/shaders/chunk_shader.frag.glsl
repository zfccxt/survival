#version 450

layout (location = 0) in vec2 v_tex;

layout (location = 0) out vec4 o_colour;

layout(binding = 1) uniform sampler2D u_floor_texture;

layout(binding = 2) uniform sampler2DArray u_floor_textures;

void main() {
  o_colour = texture(u_floor_texture, v_tex);
}
