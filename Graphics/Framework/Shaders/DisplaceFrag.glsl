#version 400

uniform sampler2D heightMap;

in Vertex {
	vec2 texCoord;
} IN;

out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = texture(heightMap, IN.texCoord);
}