#version 400

in vec3 diffuse_color;
out vec4 frag_color;

void main() {
  frag_color = vec4(diffuse_color, 1.0);
}
