#version 330 core

in DATA{
	vec3 color;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	color = vec4(fs_in.color,1.0);
}