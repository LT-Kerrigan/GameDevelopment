// Step 1: assign base color for the frag then compute the frag’s cell and pos
// Step 2: determines whether any of the neighboring cells contain a glyph which
//         contributes to the fragment currently being computed

#version 400

#define TWO_PI 6.28318

uniform vec4 model_color;
uniform sampler2D glyph_tex;
uniform sampler2D random_tex;
uniform float col_adjust;
uniform float scale_factor;
uniform float percentage;
uniform float samples_percell;
uniform float RO1;
uniform bool random_scale;
uniform bool random_rotate;
in vec2 tex_coord;
in float light_intensity;
out vec4 frag_color;

void main() {
  vec4 color  = model_color;
  vec2 cell   = floor(tex_coord);
  vec2 offset = fract(tex_coord);
  vec2 dPdx   = dFdx( tex_coord )/scale_factor;
  vec2 dPdy   = dFdy( tex_coord )/scale_factor;

  for (int i = -1; i <= int (random_rotate); i++){
    for (int j = -1; j <= int (random_rotate); j++){
      vec2 current_cell = cell + vec2(float(i), float(j));
      vec2 current_offset = offset - vec2(float(i), float(j));
      vec2 random_UV = current_cell * vec2(RO1);

      for (int k = 0; k < int (samples_percell); k++){
        vec4 random = textureGrad(random_tex, random_UV, dPdx, dPdy);
        random_UV += random.ba;

        if (random.r < percentage){
          vec2 glyph_index;
          mat2 rotator;
          vec2 index;
          float rotation_angle, cos_rot, sin_rot;
          index.s = floor(random.b * 10.0);
          index.t = floor(col_adjust * 10.0);

          if (random_rotate) {
            rotation_angle = TWO_PI * random.g;
            cos_rot = cos(rotation_angle);
            sin_rot = sin(rotation_angle);
            rotator[0] = vec2(cos_rot, sin_rot);
            rotator[1] = vec2(-sin_rot, cos_rot);
            glyph_index = -rotator * (current_offset - random.rg);
          }
          else {
            glyphIndex = currentOffset - random.rg;
          }
          if (random_scale) glyph_index /= vec2(0.5 * random.r + 0.5);

          glyph_index = (clamp(glyph_index, 0.0, 1.0) + index) * 0.1;
          vec4 image = textureGrad(glyph_tex, glyph_index,dPdx, dPdy);
          if (image.r != 1.0) color.rgb = mix(random.rgb * 0.7, color.rgb, image.r);

        }
      }
    }
  }
  frag_color = color * light_intensity;
}
