// Creates an Equirectangular environment map by using two angles
// (altitude and azimuth which will be mapped inside the texture)
// this is an alternative for cube mapping

#version 400

//TODO: put these in layout format
in vec4 mc_vertex; //model coords
in vec3 mc_normal; //model normal

//TODO: put these in an OUT block
out vec3 normal;
out vec3 eye_dir;
out float light_intensity;

//TODO: put these in an uniform block
uniform vec3 light_position;
uniform mat4 mv_matrix; //model view mv_matrix
uniform mat4 mvp_matrix; //model view projection mvp_matrix
uniform mat3 normal_matrix;

// this approach allows for reflection vector to be computed in fragment shader
void main(){
  gl_Position     = mvp_matrix * mc_vertex; //transform current incoming vertex position from model space to world space
  normal          = normalize(normal_matrix * mc_normal);
  vec4 pos        = mv_matrix * mc_vertex;
  eye_dir         = pos.xyz;
  vec3 light_dir  = normalize(light_position - eye_dir);
  light_intensity = max(dot(light_dir, normal), 0.0);
}
