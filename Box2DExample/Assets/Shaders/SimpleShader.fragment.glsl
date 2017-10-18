#version 400

layout ( location = 0 ) out vec4 out_Colour;

in vec4 ex_Position;
in vec4 ex_PositionWorld;
in vec4 ex_Normal;
in vec4 ex_UV_x2;

uniform vec3 colour;

uniform vec3 eye;

void main(void)
{
	vec3 value = colour * 0.01f+ eye * 0.01f;
	out_Colour = vec4(value + ex_Normal.xyz, 1.0f);
	return;
}
