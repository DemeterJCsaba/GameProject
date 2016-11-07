#version 420 core

in DATA{
	vec2 position;
	vec3 color;
	float texId;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	color = vec4(fs_in.color,1.0);
}