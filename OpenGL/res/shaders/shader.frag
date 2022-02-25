#version 330 core

out vec4 color;

uniform float u_Color;

void main()
{
	color = vec4(u_Color, 0.0, 0.0, 1.0);
}