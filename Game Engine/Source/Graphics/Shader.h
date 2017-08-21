#pragma once

#include <Gl\glew.h>
#include "..\Math\Vector4.h"
#include "..\Utilities\Utilities.h"

class Shader {

public:

	Shader() {}
	Shader(const char* vertFile, const char* fragFile);
	~Shader();

	const GLuint getUniformLocation(const char* name);
	
	void setImage(const GLuint& imageID);
	void setColor(const Vector4& color);

	void setUniform1i(const GLuint& id, const char* name);
	void setUniform2f(const Vector2& vec, const char* name);
	void setUniform3f(const Vector3& vec, const char* name);
	void setUniform4f(const Vector4& vec, const char* name);

	const GLuint getAttribLocation(const char* name);

	void enable();
	void disable();

private:
	GLuint id;
};

