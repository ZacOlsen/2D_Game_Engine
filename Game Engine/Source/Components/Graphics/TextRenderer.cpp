#include "TextRenderer.h"
#include "..\..\Misc\GameObject.h"

TextRenderer::TextRenderer(const char* str, const float& size, const TextJustification& just, const Vector4& color) :
	Renderer(color, nullptr) {

	justification = just;
	createText(str, size);
}

TextRenderer::~TextRenderer() {

	using namespace ftgl;

	if (atlas) {
		texture_atlas_delete(atlas);
	}

	if (font) {
		texture_font_delete(font);
	}

	if (normTextCoords) {
		delete[] normTextCoords;
	}

	if (textDims) {
		delete[] textDims;
	}

	if (penPos) {
		delete[] penPos;
	}
}

string TextRenderer::getSaveString() {

	string save = "TextRenderer\n";
	save += display + "\n";
	save += to_string(size) + "\n";
	save += to_string(justification) + "\n";
	save += to_string(color.x) + ", " + to_string(color.y) + ", " + to_string(color.z) + ", " + to_string(color.w) + "\n";

	return save;
}

TextRenderer* TextRenderer::createFromString(const string& str) {

	int start = 0;
	int end = str.find('\n', start);
	string word = str.substr(start, end - start);

	start = end + 1;
	end = str.find('\n', start);
	float size = std::stof(str.substr(start, end - start));

	start = end + 1;
	end = str.find('\n', start);
	TextJustification just = (TextJustification)std::stoi(str.substr(start, end - start));

	start = end + 1;
	end = str.find(',', start);
	float xc = std::stof(str.substr(start, end - start));

	start = end + 1;
	end = str.find(',', start);
	float yc = std::stof(str.substr(start, end - start));

	start = end + 1;
	end = str.find(',', start);
	float zc = std::stof(str.substr(start, end - start));

	start = end + 1;
	end = str.find('\n', start);
	float wc = std::stof(str.substr(start, end - start));
	Vector4 color = Vector4(xc, yc, zc, wc);

	return new TextRenderer(word.c_str(), size, just, color);
}

void TextRenderer::createText(const char* str, const float& size) {

	if (str == "" || size == 0 || (!strcmp(display.c_str(), str) && this->size == size)) {
		return;
	}

	display = str;
	this->size = size;

	using namespace ftgl;
	
	if (atlas) {
		texture_atlas_delete(atlas);
	}

	if (font) {
		texture_font_delete(font);
	}

	if (normTextCoords) {
		delete[] normTextCoords;
	}

	if (textDims) {
		delete[] textDims;
	}

	if (penPos) {
		delete[] penPos;
	}

	atlas = texture_atlas_new(512, 512, 2);
	font = texture_font_new_from_file(atlas, size, "..\\Game Engine\\Assets\\Fonts\\arial.ttf");

//	height = font->ascender - font->descender;

	width = 0;
	findFontHeight();

	normTextCoords = new Vector2[2 * display.length()];
	textDims = new Vector2[display.length()];
	penPos = new Vector2[display.length()];

	for (unsigned int i = 0; i < display.length(); i++) {

		texture_glyph_t* glyph = texture_font_get_glyph(font, display[i]);

		normTextCoords[i * 2].x = glyph->s0;
		normTextCoords[i * 2].y = glyph->t1;
		normTextCoords[i * 2 + 1].x = glyph->s1;
		normTextCoords[i * 2 + 1].y = glyph->t0;

		textDims[i].x = (float)glyph->width;
		textDims[i].y = (float)glyph->height;

		penPos[i].x = glyph->advance_x;// - glyph->offset_x;
		penPos[i].y = glyph->offset_y - textDims[i].y;
//		penPos[i].y = glyph->offset_y;
/*
		cout << text[i] << endl;
		cout << "width " << glyph->width << endl;
		cout << "height " << glyph->height << endl;
		cout << "adv x " << glyph->advance_x << endl;
		cout << "adv y " << glyph->advance_y << endl;
		cout << "off x " << glyph->offset_x << endl;
		cout << "off y " << glyph->offset_y << endl << endl;
*/
		width += penPos[i].x;
	}
}

void TextRenderer::findFontHeight() {
	
	using namespace ftgl;
	texture_glyph_t* glyph = texture_font_get_glyph(font, 'a');
	height = (float)glyph->height;
}

const GLuint TextRenderer::getTextureID(const unsigned int& index) {
	return atlas->id;
}

void TextRenderer::render() {

	Vector2 pos;

	switch (justification) {

	case LEFT:
		pos = Vector2();
		break;

	case CENTER:
		pos = Vector2(-width / 2.0f, 0);
		break;

	case RIGHT:
		pos = Vector2(-width, 0);
		break;
	}

	for (unsigned int i = 0; i < display.length(); i++) {

		if (i > 0) {
			pos.x += penPos[i - 1].x;
		}

		pos.y = penPos[i].y;
//		pos.y = (height / 2.0f) - (height / 2.0f - penPos[i].y);
//		pos.y = font->ascender - (height / font->ascender) * (font->ascender - penPos[i].y);

		Vector2 botL = Vector2(pos.x, pos.y);
		Vector2 botR = Vector2(pos.x + textDims[i].x, pos.y);
		Vector2 topR = Vector2(pos.x + textDims[i].x, pos.y + textDims[i].y);
		Vector2 topL = Vector2(pos.x, pos.y + textDims[i].y);

		gameObject->transform->getCameraPerspectivePosition(botL, botR, topR, topL);

		uvs.clear();
		uvs.push_back(Vector2(normTextCoords[i * 2]));
		uvs.push_back(Vector2(normTextCoords[i * 2 + 1].x, normTextCoords[i * 2].y));
		uvs.push_back(Vector2(normTextCoords[i * 2 + 1].x, normTextCoords[i * 2 + 1].y));
		uvs.push_back(Vector2(normTextCoords[i * 2].x, normTextCoords[i * 2 + 1].y));

//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, atlas->id);
		renderSprite(botL, botR, topR, topL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
