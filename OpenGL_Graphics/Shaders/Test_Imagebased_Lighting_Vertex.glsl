#version 400

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;
in vec4 mc_vertex;
in vec3 mc_normal;

out vec3 reflect_dir;
out vec3 normal;

void main() {
  gl_Position = mvp_matrix * mc_vertex;
  normal = normalize(normal_matrix * mc_normal);
  vec4 pos = mv_matrix * mc_vertex;
  vec3 eyeDir = pos.xyz;
  reflect_dir = reflect(eye_dir, normal);
}
