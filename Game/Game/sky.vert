#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in float textureId;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 rot_matrix = mat4(1.0);

out DATA{
	vec2 PlanetTexture;
	vec3 tex;
	vec3 tex2;
	float texId;
} vs_out;

void main(void){
	vs_out.PlanetTexture = texture;

	vec4 rot = rot_matrix * position;

	gl_Position = pr_matrix * vw_matrix * rot;
	vs_out.tex = rot.xyz;
	vs_out.tex2 = position.xyz;
	vs_out.texId = textureId;
}