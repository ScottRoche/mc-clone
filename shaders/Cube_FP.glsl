#version 330 core

in vec3 Color;
in vec2 TexCoord;
flat in float TexIndex;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	switch(int(TexIndex))
	{
		case 0: FragColor = texture(texture0, TexCoord); break;
		case 1: FragColor = texture(texture1, TexCoord); break;
		case 2: FragColor = texture(texture2, TexCoord); break;
		default: break;
	}
}