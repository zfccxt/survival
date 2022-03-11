#version 450

layout (location = 0) in vec3 a_pos;

layout (binding = 0) uniform ViewProjectionMatrix {
  mat4 matrix;
} u_viewprojection;

void main() {
  gl_Position = u_viewprojection.matrix * vec4(a_pos, 1);
}
