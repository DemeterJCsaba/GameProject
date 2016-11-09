#version 420 core

uniform sampler2D SkyColors;
uniform samplerCube SkyBoxTexture;
uniform sampler2D sunTexture;
uniform sampler2D moonTexture;

in DATA{
	vec2 PlanetTexture;
	vec3 tex;
	vec3 tex2;
	float texId;
} fs_in;

layout (location = 0) out vec4 color;

void main(void){
	if(fs_in.texId > 0.5){ // Sun and Moon
		if(fs_in.texId < 1.5)
			color = texture(sunTexture,fs_in.PlanetTexture);
		else
			color = texture(moonTexture,fs_in.PlanetTexture);

	}else{ // Sky
		//vec3 nor = normalize(fs_in.tex);
		color = texture(SkyBoxTexture,-fs_in.tex2);
	}
}