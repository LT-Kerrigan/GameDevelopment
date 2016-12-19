#version 400

uniform vec3 base_color;
uniform float specular_percent;
uniform float diffuse_percent;
uniform samplerCube specular_envmap;
uniform samplerCube diffuse_envmap;

in vec3 reflect_dir;
in vec3 normal;
out vec4 frag_color;

void main() {
  // Look up environment map values in cube maps
  vec3 diffuse_color  = vec3(texture(diffuse_envmap, normalize(normal)));
  vec3 specular_color = vec3(texture(specular_envmap, normalize(reflect_dir)));
  // Add lighting to base color and mix
  vec3 color = mix(base_color, diffuse_color*base_color, diffuse_percent);
  color = mix(color, specular_color + color, specular_percent);
  frag_color = vec4(color, 1.0);
}
