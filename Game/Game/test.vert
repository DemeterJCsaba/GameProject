#version 420 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in float textureId;

out DATA{
	vec2 position;
	vec3 color;
	float texId;
} vs_out;

void main(void){

	gl_Position = vec4(position,0.0,1.0);
	vs_out.position = position.xy;
	vs_out.color = color;
	vs_out.texId = textureId;
}