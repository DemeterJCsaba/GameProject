#pragma once

#include <GLEW\glew.h> 
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class ShaderProgram {
private:
	GLuint m_ShaderID;

	string m_Name;
public:
	ShaderProgram(string name);
	ShaderProgram();
	void enable() const;
	void disable() const;
};