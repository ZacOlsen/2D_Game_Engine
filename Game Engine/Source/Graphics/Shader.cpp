#include "Shader.h"

Shader::Shader(const char* vertFile, const char* fragFile) {

	id = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	string vertFP = "..\\Game Engine\\Source\\Shaders\\" + string(vertFile);
	string fragFP = "..\\Game Engine\\Source\\Shaders\\" + string(fragFile);

	string fragProgs = Utilities::readFile(fragFP.c_str());
	string vertProgs = Utilities::readFile(vertFP.c_str());
	const char* fragProg = fragProgs.c_str();
	const char* vertProg = vertProgs.c_str();

	glShaderSource(vertex, 1, &vertProg, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		std::cout << vertFile << " failed" << std::endl;
		return;
	}

	glShaderSource(fragment, 1, &fragProg, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		std::cout << fragFile << " failed" << std::endl;
		return;
	}

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);

	glLinkProgram(id);
	glValidateProgram(id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader() {
}

const GLuint Shader::getUniformLocation(const char* name) const {
	return glGetUniformLocation(id, name);
}

void Shader::setUniform1i(const GLuint& id, const char* name) const {
	glUniform1i(getUniformLocation(name), id);
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Shader::setUniform1f(const float& f, const char* name) const {
	glUniform1f(getUniformLocation(name), f);
}

void Shader::setUniform2f(const Vector2& vec, const char* name) const {
	glUniform2f(getUniformLocation(name), vec.x, vec.y);
}

void Shader::setUniform3f(const Vector3& vec, const char* name) const {
	glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::setUniform4f(const Vector4& vec, const char* name) const {
	glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

const GLuint Shader::getAttribLocation(const char* name) const {
	return glGetAttribLocation(id, name);
}

void Shader::enable() const {
	glUseProgram(id);
}

void Shader::disable() const {
	glUseProgram(0);
}
