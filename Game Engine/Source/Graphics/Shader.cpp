#include "Shader.h"

Shader::Shader(const char* vertFile, const char* fragFile) {

	id = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	string fragProgs = Utilities::readFile(fragFile);
	string vertProgs = Utilities::readFile(vertFile);
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

const GLuint Shader::getUniformLocation(const char* name) {
	return glGetUniformLocation(id, name);
}

void Shader::setImage(const GLuint& imageID) {

	GLuint loc = glGetUniformLocation(id, "image");
	glUniform1i(loc, imageID);
}

void Shader::addImage(const GLuint& textureID, const char* imageLocName) {

	if (textureIDs.size() >= 32) {
		throw exception();
	}

	for (unsigned int i = 0; i < textureIDs.size(); i++) {
		if (textureIDs[i] == textureID) {
			return;
		}
	}

	textureIDs.push_back(textureID);
	imageLocNames.push_back(imageLocName);
}

void Shader::setColor(const Vector4& color) {
 
	GLuint loc = glGetUniformLocation(id, "spriteColor");
	glUniform4f(loc, color.x, color.y, color.z, color.w);
}

void Shader::setUniform1i(const GLuint& id, const char* name) {
	glUniform1i(getUniformLocation(name), id);
}

void Shader::setUniform2f(const Vector2& vec, const char* name) {
	glUniform2f(getUniformLocation(name), vec.x, vec.y);
}

void Shader::setUniform3f(const Vector3& vec, const char* name) {
	glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::setUniform4f(const Vector4& vec, const char* name) {
	glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

const GLuint Shader::getAttribLocation(const char* name) {
	return glGetAttribLocation(id, name);
}

void Shader::enable() {

	glUseProgram(id);

	for (unsigned int i = 0; i < textureIDs.size(); i++) {
		
		setUniform1i(textureIDs[i], imageLocNames[i].c_str());
		glActiveTexture(GL_TEXTURE0 + textureIDs[i]);
		glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
	}
}

void Shader::disable() {
	glUseProgram(0);
}
