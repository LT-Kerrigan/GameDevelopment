#version 400

uniform vec3 brick_color, mortar_color;
uniform vec2 brick_size;
uniform vec2 brick_pct;

in vec2 mc_position;
in vec2 light_intensity;

out vec4 frag_color;

void main() {
  //brick row/number position
  vec2 position = mc_position / brick_size;

  if(fract(position.y * 0.5) > 0.5) {
    position.x = 0.5;
  }

  //compute fragment's location within current brick
  position = fract(position);
  vec2 use_brick = step(position, brick_pct);

  vec3 color = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);
  color *= LightIntensity;
  frag_color = vec4(color, 1.0);

}
