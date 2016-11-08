#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(string name):
	m_Name(name)
{
	m_ShaderID = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint geometry = glCreateShader(GL_GEOMETRY_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// Load and compile Vertex Shader Program
	ifstream vertexFile(name + ".vert");
	if (vertexFile.good()) {
		string vertSourceString((istreambuf_iterator<char>(vertexFile)), istreambuf_iterator<char>());
		const char* vertSource = vertSourceString.c_str();

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

		glAttachShader(m_ShaderID, vertex);
	}

	// Load and compile Geometry Shader Program
	ifstream geometryFile(name + ".geom");
	if (geometryFile.good()) {
		string geomSourceString((istreambuf_iterator<char>(geometryFile)), istreambuf_iterator<char>());
		const char* geomSource = geomSourceString.c_str();

		glShaderSource(geometry, 1, &geomSource, NULL);
		glCompileShader(geometry);

		GLint result;
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(geometry, GL_INFO_LOG_LENGTH, &length);
			vector<char> error(length);
			glGetShaderInfoLog(geometry, length, &length, &error[0]);
			cout << "Faild to compile geometry shader: " << &error[0] << endl;
			glDeleteShader(geometry);
			// Todo: Throw exception
		}

		glAttachShader(m_ShaderID, geometry);
	}

	// Load and compile Fragment Shader Program
	ifstream fragmentFile(name + ".frag");
	if(fragmentFile.good()) {
		string fragSourceString((istreambuf_iterator<char>(fragmentFile)), istreambuf_iterator<char>());
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		GLint result;
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

		glAttachShader(m_ShaderID, fragment);
	}
	
	glLinkProgram(m_ShaderID);
	glValidateProgram(m_ShaderID);

	glDeleteShader(vertex);
	glDeleteShader(geometry);
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

// Uniforms - Load data to Shader Program
GLuint ShaderProgram::getUniformLocation(const GLchar* name) {
	if (m_Uniforms.find(name) == m_Uniforms.end()) {
		m_Uniforms[name] = glGetUniformLocation(m_ShaderID, name);
	}
	return m_Uniforms[name];
}

void ShaderProgram::setUniform1i(const GLchar* name, int value) {
	glUniform1i(getUniformLocation(name), value);
}

void ShaderProgram::setUniformiv(const GLchar* name, int* value, int count) {
	glUniform1iv(getUniformLocation(name), count, value);
}

void ShaderProgram::setUniform1f(const GLchar* name, float value) {
	glUniform1f(getUniformLocation(name), value);
}

void ShaderProgram::setUniform2f(const GLchar* name, const vec2& vector) {
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void ShaderProgram::setUniform3f(const GLchar* name, const vec3& vector) {
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void ShaderProgram::setUniform4f(const GLchar* name, const vec4& vector) {
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::setUniformMat4(const GLchar* name, const mat4& matrix) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FLOAT, matrix.elements);
}