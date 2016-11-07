#pragma once

#include <GLEW\glew.h> 
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <map>

#include "Maths.h"

using namespace std;

class ShaderProgram {
private:
	GLuint m_ShaderID;
	string m_Name;

	map<string, GLuint> m_Uniforms;
public:
	ShaderProgram(string name);
	ShaderProgram();
	void enable() const;
	void disable() const;

	void setUniform1i(const GLchar* name, int value);
	void setUniformiv(const GLchar* name, int* value, int count);
	void setUniform1f(const GLchar* name, float value);
	void setUniform2f(const GLchar* name, const vec2& vector);
	void setUniform3f(const GLchar* name, const vec3& vector);
	void setUniform4f(const GLchar* name, const vec4& vector);
	void setUniformMat4(const GLchar* name, const mat4& matrix);
private:
	GLuint getUniformLocation(const GLchar* name);
};