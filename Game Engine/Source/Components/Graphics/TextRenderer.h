#pragma once
#include "..\..\..\ext\freetype-gl\freetype-gl.h"
#include "Renderer.h"

enum TextJustification {
	LEFT,
	CENTER,
	RIGHT
};

class TextRenderer : public Renderer {

public:

	TextJustification justification;

	TextRenderer(const char* str, const float& size = 0, const TextJustification& just = CENTER, 
		const Vector4& color = Vector4(1, 1, 1, 1));
	~TextRenderer();
	
	string getSaveString();
	static TextRenderer* createFromString(const string& str);

	virtual const GLuint getTextureID(const unsigned int& index) override;

	void createText(const char* str, const float& size);
	void render() override;

private:

	ftgl::texture_atlas_t* atlas = NULL;
	ftgl::texture_font_t* font = NULL;

	Vector2* normTextCoords = NULL;
	Vector2* textDims = NULL;
	Vector2* penPos = NULL;

	float width = 0;
	float height = 0;
	
	string display = "";
	float size;

	void findFontHeight();
};

