#include "SpriteRenderer.h"

vector<vector<SpriteRenderer*>> SpriteRenderer::spriteRenders;

SpriteRenderer::SpriteRenderer(const Vector2& size, const Vector4& color, Sprite* sprite) :
	Renderer(color, sprite) {

	this->size = size;
	setSortingLayer(sortingLayer);

	shaderIndex = 1;
}

SpriteRenderer::SpriteRenderer(const Vector2& size, const Vector4& color, vector<Sprite*> sprites,
	vector<string> locationNames, const unsigned int& layer) : Renderer(color, sprites, locationNames) {

	this->size = size;
	setSortingLayer(layer);

	shaderIndex = 1;
}

SpriteRenderer::~SpriteRenderer() {

	Component::~Component();

	auto it = find(spriteRenders[sortingLayer].begin(), spriteRenders[sortingLayer].end(), this);
	if (it != spriteRenders[sortingLayer].end()) {
		spriteRenders[sortingLayer].erase(it);
	}
}

string SpriteRenderer::getSaveString() {

	string save = "SpriteRenderer\n";
	save += to_string(size.x) + ", " + to_string(size.y) + "\n";

	//	if (sprite) {
	//		save += sprite->getFilePath();
	//	} else {
	save += "NULL";
	//	}
	save += "\n";
	save += to_string(color.x) + ", " + to_string(color.y) + ", " + to_string(color.z) + ", " + to_string(color.w) + "\n";

	return save;
}

SpriteRenderer* SpriteRenderer::createFromString(const string& string) {

	SpriteRenderer* sr = new SpriteRenderer();

	int start = 0;
	int end = string.find(',', start);
	float xs = std::stof(string.substr(start, end - start));

	start = end + 2;
	end = string.find('\n', start);
	float ys = std::stof(string.substr(start, end - start));
	sr->size = Vector2(xs, ys);

	start = end + 1;
	end = string.find('\n', start);

	if (string.substr(start, end - start) != "NULL") {
		Sprite* s = Sprite::getSprite(string.substr(start, end - start).c_str());

		//		sr->sprite = s;
	}

	start = end + 1;
	end = string.find(',', start);
	float xc = std::stof(string.substr(start, end - start));

	start = end + 1;
	end = string.find(',', start);
	float yc = std::stof(string.substr(start, end - start));

	start = end + 1;
	end = string.find(',', start);
	float zc = std::stof(string.substr(start, end - start));

	start = end + 1;
	end = string.find('\n', start);
	float wc = std::stof(string.substr(start, end - start));
	sr->color = Vector4(xc, yc, zc, wc);

	return sr;
}

void SpriteRenderer::changeSortingLayer(const unsigned int& layer) {

	auto it = find(spriteRenders[sortingLayer].begin(), spriteRenders[sortingLayer].end(), this);
	if (it != spriteRenders[sortingLayer].end()) {
		spriteRenders[sortingLayer].erase(it);
	}

	setSortingLayer(layer);
}

void SpriteRenderer::setSortingLayer(const unsigned int& layer) {

	sortingLayer = layer;
	while (spriteRenders.size() <= layer) {
		spriteRenders.push_back(vector<SpriteRenderer*>());
	}

	spriteRenders[layer].push_back(this);
}

void SpriteRenderer::init() {

	shaders.push_back(new Shader("World.vert", "World.frag"));
	shaders.push_back(new Shader("AreaLight.vert", "AreaLight.frag"));
	spriteRenders = vector<vector<SpriteRenderer*>>();
}

void SpriteRenderer::renderAllSprites() {

	for (unsigned int i = 0; i < spriteRenders.size(); i++) {
		for (unsigned int j = 0; j < spriteRenders[i].size(); j++) {
			spriteRenders[i][j]->render();
		}
	}
}

void SpriteRenderer::render() {

	float top = size.y / 2.0f;
	float bot = -size.y / 2.0f;
	float left = -size.x / 2.0f;
	float right = size.x / 2.0f;

	Vector2 topR = Vector2(right, top);
	Vector2 topL = Vector2(left, top);
	Vector2 botL = Vector2(left, bot);
	Vector2 botR = Vector2(right, bot);

	Vector2 worldBotL = botL;
	Vector2 worldBotR = botR;
	Vector2 worldTopR = topR;
	Vector2 worldtopL = topL;

	gameObject->transform->getWorldPosition(worldBotL, worldBotR, worldTopR, worldtopL);
	gameObject->transform->getCameraPerspectivePosition(topR, topL, botL, botR);

	if (sprites.size() > 0) {

//		sprite->bind();
		renderSprite(botL, botR, topR, topL, worldBotL, worldBotR, worldTopR, worldtopL);
//		sprite->unbind();

	} else {
		renderRect(botL, botR, topR, topL);
	}
}

void SpriteRenderer::renderSprite(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL,
	const Vector2& worldBotL, const Vector2& worldBotR, const Vector2& worldTopR, const Vector2& worldTopL) const {

	shaders[shaderIndex]->enable();
	shaders[shaderIndex]->setUniform4f(color, "spriteColor");

	for (unsigned int i = 0; i < sprites.size(); i++) {
		const GLuint textureID = getTextureID(i);
		shaders[shaderIndex]->setUniform1i(textureID, locationNames[i].c_str());
	}

	const GLuint texLoc = shaders[shaderIndex]->getAttribLocation("texCoord");
	const GLuint screenPosLoc = shaders[shaderIndex]->getAttribLocation("screenPos");
	const GLuint worldPosLoc = shaders[shaderIndex]->getAttribLocation("worldPos");

	glBegin(GL_QUADS);
	glVertexAttrib2f(texLoc, uvs[0].x, uvs[0].y);
	glVertexAttrib2f(screenPosLoc, botL.x, botL.y);
	glVertexAttrib2f(worldPosLoc, worldBotL.x, worldBotL.y);
	glTexCoord2f(uvs[0].x, uvs[0].y);
	glVertex2f(botL.x, botL.y);

	glVertexAttrib2f(texLoc, uvs[1].x, uvs[1].y);
	glVertexAttrib2f(screenPosLoc, botR.x, botR.y);
	glVertexAttrib2f(worldPosLoc, worldBotR.x, worldBotR.y);
	glTexCoord2f(uvs[1].x, uvs[1].y);
	glVertex2f(botR.x, botR.y);

	glVertexAttrib2f(texLoc, uvs[2].x, uvs[2].y);
	glVertexAttrib2f(screenPosLoc, topR.x, topR.y);
	glVertexAttrib2f(worldPosLoc, worldTopR.x, worldTopR.y);
	glTexCoord2f(uvs[2].x, uvs[2].y);
	glVertex2f(topR.x, topR.y);

	glVertexAttrib2f(texLoc, uvs[3].x, uvs[3].y);
	glVertexAttrib2f(screenPosLoc, topL.x, topL.y);
	glVertexAttrib2f(worldPosLoc, worldTopL.x, worldTopL.y);
	glTexCoord2f(uvs[3].x, uvs[3].y);
	glVertex2f(topL.x, topL.y);
	glEnd();

	shaders[shaderIndex]->disable();
}

