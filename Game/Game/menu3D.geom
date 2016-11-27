#version 150

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

in DATA{
	vec3 normal;
	vec3 color;
} gs_in[3];

out DATA{
	vec3 color;
} gs_out;

uniform vec3 sunPosition = vec3(0.5,0.5,0);

void main(void){
	vec3 unitNormal = normalize(gs_in[0].normal);
	vec3 unitSun    = normalize(sunPosition);
	float nDot = dot(unitNormal,unitSun);
	float inten = clamp((sunPosition.y + 0.2)*10.0 ,0.0,1.0);
	float brightness = max(nDot*inten,0.1);

	for(int i = 0; i < gl_in.length(); i++){
		gl_Position = gl_in[i].gl_Position;

		gs_out.color = mix(vec3(0.5,0.5,0.5),gs_in[0].color,nDot);
 
		EmitVertex();
	}
}