#version 400 core

layout(vertices = 4) out; //num vertices in output patch

in Vertex {
	vec2 texCoord;		  // from Vertex shader
} IN[];					  // equal to size of draw call vertex count

out Vertex {
	vec2 texCoord;		  // to evaluation shader
} OUT[];				  // equal to the size of the layout vertex count

void main() {
	gl_TessLevelInner[0] = 16;
	gl_TessLevelInner[1] = 16;
	gl_TessLevelOuter[0] = 16;
	gl_TessLevelOuter[1] = 16;
	gl_TessLevelOuter[2] = 16;
	gl_TessLevelOuter[3] = 16;
	
	OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_PositionID].gl_Position; 
}