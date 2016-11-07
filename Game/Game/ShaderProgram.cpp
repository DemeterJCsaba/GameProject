#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(string name):
	m_Name(name)
{
	m_ShaderID = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	// geometry
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	ifstream vertexFile(name + ".vert");
	ifstream fragmentFile(name + ".frag");
	string vertSourceString((istreambuf_iterator<char>(vertexFile)),istreambuf_iterator<char>());
	string fragSourceString((istreambuf_iterator<char>(fragmentFile)), istreambuf_iterator<char>());

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		cout << "Faild to compile vertex shader: " << &error[0] << endl;
		glDeleteShader(vertex);
		// Todo: Throw exception
	}

	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		cout << "Faild to compile fragment shader: " << &error[0] << endl;
		glDeleteShader(fragment);
		// Todo: Throw exception
	}

	glAttachShader(m_ShaderID, vertex);
	glAttachShader(m_ShaderID, fragment);

	glLinkProgram(m_ShaderID);
	glValidateProgram(m_ShaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderProgram::ShaderProgram() {
	glDeleteProgram(m_ShaderID);
}

void ShaderProgram::enable() const {
	glUseProgram(m_ShaderID);
}

void ShaderProgram::disable() const {
	glUseProgram(0);
}