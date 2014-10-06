#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 textureMatrix;

uniform sampler2D vertexTexture;
uniform vec3 vertexHeight;

in vec3 position;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;
layout (location = 7) in vec3 rndPos;

out Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} OUT;

void main(void){

	OUT.colour = colour;
	OUT.texCoord = (textureMatrix * vec4(texCoord, 0.0, 1.0)).xy;
	
	vec3 axisRot = vec3(0,position.y + 1,0);
	float angleRot = rndPos.y;
	
	axisRot.x = dot(vec3(cos(angleRot), 0.0, -sin(angleRot)), position);
	axisRot.z = dot(vec3(sin(angleRot), 0.0, cos(angleRot)), position);
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
	OUT.normal = normalize(normalMatrix * normalize(normal)); 
	OUT.worldPos = (modelMatrix * vec4(axisRot, 1)).xyz;
	
	OUT.worldPos += rndPos; 
	
	vec2 currentTex = vec2(OUT.worldPos.z / vertexHeight.z, OUT.worldPos.x / vertexHeight.x);
	float height = textureLod(vertexTexture, currentTex, 0.0).x * 255.0 * vertexHeight.y;
	
    vec4 pos = vec4(axisRot.x, axisRot.y, axisRot.z, 1.0);
	
	OUT.worldPos = (modelMatrix * pos).xyz;
	OUT.worldPos.y += height;
	OUT.worldPos.xz += rndPos.xz;
	
    gl_Position = (projMatrix * viewMatrix ) * vec4(OUT.worldPos, 1.0);
}