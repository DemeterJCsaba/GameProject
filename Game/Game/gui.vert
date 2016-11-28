#version 420 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in float textureId;

out DATA{
	vec2 position;
	vec2 texture;
	float texId;
} vs_out;

void main(void){
	gl_Position = vec4(position,0.0,1.0);

	vs_out.position = position;
	vs_out.texture = texture;
	vs_out.texId = textureId;
}