#version 420 core
 
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

in DATA{
	vec3 normal;
	vec3 color;
	float visibility;
} gs_in[3];

out DATA{
	vec3 color;
} gs_out;

uniform sampler2D SkyGradient;

uniform vec3 sunPosition = vec3(1,0,0);
uniform float time = 0.0;

void main(void){
	vec3 unitNormal = normalize(gs_in[0].normal);
	vec3 unitSun    = normalize(sunPosition);
	float nDot = dot(unitNormal,unitSun);
	float inten = clamp((sunPosition.y + 0.2)*10.0 ,0.0,1.0);//max( sunPosition.y * 100 , 0.0 );
	float brightness = max(nDot*inten,0.2);
	float t = time/360.0;
	vec3 fogColor = texture(SkyGradient,vec2(t,0.02)).xyz;
	vec3 diffuse = brightness * fogColor;

	for(int i = 0; i < gl_in.length(); i++){
		gl_Position = gl_in[i].gl_Position;

		//gs_out.color = mix(fogColor,diffuse * gs_in[0].color,gs_in[i].visibility);
		gs_out.color = mix(fogColor,diffuse * mix(vec3(1.0,1.0,0.8),gs_in[0].color,0.9),gs_in[i].visibility);
 
		EmitVertex();
	}
}