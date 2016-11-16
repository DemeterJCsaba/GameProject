#version 420 core

uniform sampler2D SkyGradient;
uniform samplerCube SkyBoxTexture;
uniform sampler2D sunTexture;
uniform sampler2D moonTexture;

uniform vec3 sunPosition = vec3(1,0,0);
uniform float time = 0.0;

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
		float dayNightFactor = clamp(((sunPosition.y+0.05)*(-4)),0.0,1.0);

		vec3 nor = normalize(fs_in.tex);
		vec4 day;
		float tmp = time/360.0;
		if(nor.y>0.001){
			day = texture(SkyGradient,vec2(tmp,nor.y*0.99));
		}else{
			day = texture(SkyGradient,vec2(tmp,0.02));
		}
		vec4 night = texture(SkyBoxTexture,-fs_in.tex2) + day;

		color = mix(day,night,dayNightFactor);
	}
}