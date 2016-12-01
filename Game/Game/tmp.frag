#version 420 core

uniform sampler2D SkyGradient;

uniform vec3 sunPosition = vec3(1,0,0);
uniform float time = 0.0;

in DATA{
	vec3 normal;
	vec3 color;

	float visibility;
} fs_in;


layout (location = 0) out vec4 color;

void main(void){
	vec3 unitNormal = normalize(fs_in.normal);
	vec3 unitSun    = normalize(sunPosition);
	float nDot = dot(unitNormal,unitSun);
	float inten = clamp((sunPosition.y + 0.2)*10.0 ,0.0,1.0);
	float brightness = max(nDot*inten,0.1);
	float t = time/360.0;
	vec3 fogColor = texture(SkyGradient,vec2(t,0.02)).xyz;
	vec3 diffuse = brightness * fogColor;

	color = vec4(mix(fogColor,diffuse * fs_in.color,fs_in.visibility),1.0);
}