#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);

uniform float dentity = 0.001; 
uniform float gradient = 3.0;

out DATA{
	vec3 normal;
	vec3 color;
	float visibility;
} vs_out;

void main(void){
	gl_Position = pr_matrix * vw_matrix * vec4(position,1.0);

	float distance = length((vw_matrix * vec4(position,1.0)).xyz);
	vs_out.visibility = exp(-pow((distance*dentity),gradient));
	vs_out.visibility = clamp(vs_out.visibility,0.0,1.0);

	vs_out.normal = normal;
	vs_out.color = color;
}