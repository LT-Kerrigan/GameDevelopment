#version 400

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;
uniform vec3 w_light_pos;   // Position of light in world coordinates
uniform vec4 view_position; // Position of camera in world space
uniform mat4 w_to_l;        // World to light coordinate transform
uniform mat4 w_to_lit;      // World to light inverse transpose
uniform mat4 mc_to_w;       // Model to world coordinate transform
uniform mat4 mc_to_wit;     // Model to world inverse transpose

in vec4 mc_vertex;
in vec3 mc_normal;
out vec3 lc_pos;    // Vertex position in light coordinates
out vec3 lc_norm;   // Normal in light coordinates
out vec3 lc_camera; // Camera position in light coordinates

void main() {
  gl_Position = mvp_matrix * mc_vertex;
  // Compute world space position and normal
  vec4 w_pos = mc_to_w * mc_vertex;
  vec3 w_norm = (mc_to_wit * vec4(mc_normal, 0.0)).xyz;
  // Compute light coordinate system camera position,
  // vertex position and normal
  lc_camera = (w_to_l * view_position).xyz;
  lc_pos = (w_to_l * w_pos).xyz;
  lc_norm = (w_to_lit * vec4(w_norm, 0.0)).xyz;
}
