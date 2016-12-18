#version 400
uniform vec3 light_position;
uniform vec3 sky_color;
uniform vec3 ground_color;

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;
in vec4 mc_vertex;
in vec3 mc_normal;
out vec3 color;

void main() {
  vec3 ec_position = vec3(mv_matrix * mc_vertex);
  vec3 tnorm = normalize(normal_matrix * mc_normal);
  vec3 light_vec = normalize(light_position - ec_position);
  float costheta = dot(tnorm, light_vec);
  float a = costheta * 0.5 + 0.5;
  color = mix(ground_color, sky_color, a);
  gl_Position = mvp_matrix * mc_vertex;
}
