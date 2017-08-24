#pragma once

#include <Gl\glew.h>
#include "..\Math\Vector4.h"
#include "..\Utilities\Utilities.h"

class Shader {

public:

	Shader() {}
	Shader(const char* vertFile, const char* fragFile);
	~Shader();

	const GLuint getUniformLocation(const char* name) const;
	
	void setUniform1i(const GLuint& id, const char* name) const;
	void setUniform1f(const float& f, const char* name) const;
	void setUniform2f(const Vector2& vec, const char* name) const;
	void setUniform3f(const Vector3& vec, const char* name) const;
	void setUniform4f(const Vector4& vec, const char* name) const;

	const GLuint getAttribLocation(const char* name) const;

	void enable() const;
	void disable() const;

private:
	GLuint id;
};

