// Grid-based texturing for adding decorative elements from a glyph texture;
// The scaled texture coordinates are passed to frag shader;
// This will be a frame of reference for defining cells where glyphs will appear.

#version 400

in vec4 mc_vertex;
in vec3 mc_normal;

out vec3 normal;
out vec2 tex_coord;
out float light_intensity;

uniform float specular_contribution;
uniform float scale_factor;
uniform vec3  light_position;

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;

void main() {
  vec3 ec_position = vec3(mv_matrix * mc_vertex);
  vec3 tnorm       = normalize(normal_matrix * mc_normal);
  vec3 light_vec   = normalize(light_position - ec_position);
  vec3 reflect_vec = reflect(-light_vec, tnorm);
  vec3 view_vec    = normalize(-ec_position);

  float diffuse = max(dot(light_vec, tnorm), 0.0);
  float spec = 0.0;

  if(diffuse > 0.0) {
    spec = max(dot(reflect_vec, view_vec), 0.0);
    spec = pow(spec, 16.0);
  }

  float diffuse_contribution = 1.0 - specular_contribution;
  light_intensity = diffuse_contribution * diffuse * 2.0 + specular_contribution * spec;
  tex_coord = tex_coord0.st * scale_factor;
  gl_Position = mvp_matrix * mc_vertex;
}
