#version 450

layout (location = 0) in vec3 v_tex;

layout (location = 0) out vec4 o_colour;

layout(binding = 1) uniform sampler2DArray u_floor_texture_array;

void main() {
  o_colour = texture(u_floor_texture_array, v_tex);
}
