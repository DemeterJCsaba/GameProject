#version 420 core

in DATA{
	vec3 position;
	vec3 normal;
	vec3 color;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	color = vec4(0.0,0.7,0.0,1.0);
}