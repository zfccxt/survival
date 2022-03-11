#version 450

layout (location = 0) in vec2 v_tex;

layout (location = 0) out vec4 o_colour;

void main() {
  o_colour = vec4(v_tex, 0.0, 1.0);
}
