#include "Renderer.h"
#include "..\..\Misc\GameObject.h"

vector<Shader*> Renderer::shaders;

Renderer::Renderer(const Vector4& color, Sprite* sprite) {

	this->color = color;

	sprites.push_back(sprite);
	locationNames.push_back("image");

	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 1));
}

Renderer::Renderer(const Vector4& color, vector<Sprite*> sprites, vector<string> locationNames) {

	this->color = color;
	this->sprites = sprites;
	this->locationNames = locationNames;

	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 1));
}

void Renderer::init() {
	shaders.push_back(new Shader("UI.vert", "UI.frag"));
}

std::string Renderer::getSaveString() {
	
	string save = "Renderer\n";

//	if (sprite) {
	//	save += sprite->getFilePath();
//	} else {
		save += "NULL";
//	}
	save += "\n";
	save += to_string(color.x) + ", " + to_string(color.y) + ", " + to_string(color.z) + ", " + to_string(color.w) + "\n";
	
	return save;
}

Renderer* Renderer::createFromString(const string& str) {

	Renderer* rend = new Renderer();

	int start = 0;
	int end = str.find('\n', start);

	if (str.substr(start, end - start) != "NULL") {
		Sprite* s = Sprite::getSprite(str.substr(start, end - start).c_str());
	//	rend->sprite = s;
	}

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
	rend->color = Vector4(xc, yc, zc, wc);

	return rend;
}

void Renderer::setShaderIndex(const unsigned int& index) {
	shaderIndex = index;
}

Shader* Renderer::getShader(const unsigned int& index) {
	return shaders[index];
}

void Renderer::setSprites(const vector<Sprite*>& sprites) {
	this->sprites = sprites;
}

const GLuint Renderer::getTextureID(const unsigned int& index) const {
	return sprites[index]->getTextureID();
}

void Renderer::render() {

	float top = .5f;
	float bot = -.5f;
	float left = -.5f;
	float right = .5f;

	Vector2 botL(left, bot);
	Vector2 botR(right, bot);
	Vector2 topR(right, top);
	Vector2 topL(left, top);

	gameObject->transform->getCameraPerspectivePosition(topR, topL, botL, botR);

	if (sprites.size() > 0) {

//		sprite->bind();
		renderSprite(botL, botR, topR, topL);
//		sprite->unbind();

	} else {
		renderRect(botL, botR, topR, topL);
	}
}

void Renderer::renderSprite(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL) const {

	shaders[shaderIndex]->enable();
	shaders[shaderIndex]->setUniform4f(color, "spriteColor");

	for (unsigned int i = 0; i < sprites.size(); i++) {
		const GLuint textureID = getTextureID(i);
		shaders[shaderIndex]->setUniform1i(textureID, locationNames[i].c_str());
	}

	const GLuint texLoc = shaders[shaderIndex]->getAttribLocation("texCoord");
	const GLuint posLoc = shaders[shaderIndex]->getAttribLocation("screenPos");

	glBegin(GL_QUADS);
	glVertexAttrib2f(texLoc, uvs[0].x, uvs[0].y);
	glVertexAttrib2f(posLoc, botL.x, botL.y);
	glTexCoord2f(uvs[0].x, uvs[0].y);
	glVertex2f(botL.x, botL.y);

	glVertexAttrib2f(texLoc, uvs[1].x, uvs[1].y);
	glVertexAttrib2f(posLoc, botR.x, botR.y);
	glTexCoord2f(uvs[1].x, uvs[1].y);
	glVertex2f(botR.x, botR.y);

	glVertexAttrib2f(texLoc, uvs[2].x, uvs[2].y);
	glVertexAttrib2f(posLoc, topR.x, topR.y);
	glTexCoord2f(uvs[2].x, uvs[2].y);
	glVertex2f(topR.x, topR.y);

	glVertexAttrib2f(texLoc, uvs[3].x, uvs[3].y);
	glVertexAttrib2f(posLoc, topL.x, topL.y);
	glTexCoord2f(uvs[3].x, uvs[3].y);
	glVertex2f(topL.x, topL.y);
	glEnd();

	shaders[shaderIndex]->disable();
}

void Renderer::renderRect(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL) const {

	glBegin(GL_QUADS);
	glColor3f(color.x, color.y, color.z);
	glVertex2f(topR.x, topR.y);
	glVertex2f(topL.x, topL.y);
	glVertex2f(botL.x, botL.y);
	glVertex2f(botR.x, botR.y);
	glEnd();
}