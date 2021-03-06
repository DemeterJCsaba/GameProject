#version 420 core

uniform sampler2D textures[32];

uniform float fade = 0.0;

in DATA{
	vec2 position;
	vec2 texture;
	float texId;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	if(fs_in.texId > 1.5){
		color = texture(textures[int(fs_in.texId - 0.5)],fs_in.texture)*fade;
	}else{
		color = vec4(0.0,0.0,0.0,1.0-fade);
	}
}