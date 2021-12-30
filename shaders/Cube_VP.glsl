#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexIndex;

out vec3 Color;
out vec2 TexCoord;
flat out float TexIndex;

uniform mat4 proj;
uniform mat4 view;

void main()
{
	Color = aColor;
	TexCoord = aTexCoord;
	TexIndex = aTexIndex;
	gl_Position = proj * view * vec4(aPos, 1.0);
}