#version 400

in vec4 mc_vertex; //vertex in model coords
in vec3 mc_normal; // normal in model coords

uniform mat4 mv_matrix;  //model view
uniform mat4 mvp_matrix; //model view projection
uniform mat3 n_matrix;   //normal matrix
uniform vec3 light_position;

const float specular_component = 0.3; //specular contribution
const float diffuse_component  = 1.0 - specular_component;

out float light_intensity;
out vec2  mc_position;

void main() {
  vec3 ec_position = vec3(mv_matrix * mc_vertex);
  vec3 tnorm = normalize(n_matrix * mc_normal);
  vec3 light_vec = normalize(light_position - ec_position);
  vec3 reflect_vec = reflect(-light_vec, tnorm);
  vec3 view_vec = normalize(-ec_position);
  float diffuse = max(dot(light_vec, tnorm), 0.0);
  float spec = 0.0;

  if (diffuse > 0.0){
    spec = max(dot(reflect_vec, view_vec), 0.0);
    spec = pow(spec, 16.0);
  }

  light_intensity = diffuse_component * diffuse + specular_component * spec;
  mc_position = mc_vertex.xy;
  gl_Position = MVPMatrix * MCvertex;
}
