#version 400

const vec3 x_unit_vec = vec3 (1.0, 0.0, 0.0);
const vec3 y_unit_vec = vec3 (0.0, 1.0, 0.0);

//TODO: put these in uniform block
uniform vec3  base_color;
uniform float mix_ratio;
uniform sampler2D env_map; // = 4 :)

//TODO: put these in IN block
in vec3 normal;
in vec3 eye_dir;
in float light_intensity;

out vec4 frag_color;

void main() {
  vec3 reflect_dir = reflect(eye_dir, normal); //reflection vector

  vec2 index;
  index.t = dot(normalize(reflect_dir), y_unit_vec); //altitude angle
  reflect_dir.y = 0.0;
  index.s = dot(normalize(reflect_dir), x_unit_vec) * 0.5; //azimuth angles

  // gradiants computation
  vec2 dPdx = dFdx(index);
  vec2 dPdy = dFdy(index);

  // move to tec unit range
  if(reflect_dir.z >= 0.0) {
    index = (index + 1.0) * 0.5;
  }
  else {
    index.t = (index.t + 1.0) * 0.5;
    index.s = (-index.s) * 0.5 + 1.0;
  }

  // lookup in env map
  vec3 env_color = vec3(texturedGrad(env_map, index, dPdx, dPdy)););

  // add lighting to base color
  vec3 base = light_intensity * base_color;
  env_color = mix(env_color, base, mix_ratio);

  frag_color = vec4(env_color, 1.0);
}
