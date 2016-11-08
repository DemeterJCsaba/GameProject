#version 420 core

uniform sampler2D textures[32];

in DATA{
	vec2 position;
	vec3 color;
	vec2 texture;
	float texId;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	if(fs_in.texId > 0.0)
	{
		int tid = int(fs_in.texId - 0.5);
		color = texture(textures[tid],fs_in.texture); 
	}else{
		color = vec4(fs_in.color,1.0);
	}
}