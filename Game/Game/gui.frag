#version 420 core

uniform sampler2D textures[32];

in DATA{
	vec2 position;
	vec2 texture;
	float texId;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	color = texture(textures[int(fs_in.texId - 0.5)],fs_in.texture); 
}