#version 150 core

in vec4 Position;
out vec4 vPosition;

void main() 
{
	vPosition = Position.xyz;
}
