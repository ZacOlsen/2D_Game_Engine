#include "SpriteRenderer.h"

Shader SpriteRenderer::shaderWorld;
vector<SpriteRenderer*> SpriteRenderer::spriteRenders;

SpriteRenderer::SpriteRenderer(const Vector2& size, const Vector4& color, Sprite* sprite) :
	Renderer(color, sprite) {

	this->size = size;
	spriteRenders.push_back(this);

	m_shader = &shaderWorld;
}

SpriteRenderer::~SpriteRenderer() {

	auto it = find(spriteRenders.begin(), spriteRenders.end(), this);
	if (it != spriteRenders.end()) {
		spriteRenders.erase(it);
	}
}

string SpriteRenderer::getSaveString() {

	string save = "SpriteRenderer\n";
	save += to_string(size.x) + ", " + to_string(size.y) + "\n";
	
	if (sprite) {
		save += sprite->getFilePath();
	} else {
		save += "NULL";
	}
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
	//	if (s) {
			sr->sprite = s;
	//	}
	//	else {
	//		sr->sprite = new Sprite(string.substr(start, end - start).c_str());
	//	}
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

void SpriteRenderer::init() {
	shaderWorld = Shader("worldvertex.vert", "worldfragment.frag");
	spriteRenders = vector<SpriteRenderer*>();
}

void SpriteRenderer::renderAllSprites() {

	for (unsigned int i = 0; i < spriteRenders.size(); i++) {
		spriteRenders[i]->render();
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

	if (sprite) {

//		sprite->bind();
		renderSprite(botL, botR, topR, topL, worldBotL, worldBotR, worldTopR, worldtopL);
		sprite->unbind();

	} else {
		renderRect(botL, botR, topR, topL);
	}
}

void SpriteRenderer::renderSprite(const Vector2& botL, const Vector2& botR, const Vector2& topR, const Vector2& topL,
	const Vector2& worldBotL, const Vector2& worldBotR, const Vector2& worldTopR, const Vector2& worldTopL) {

	if (m_shader != &shaderWorld) {
		Sprite* s1 = Sprite::getSprite("theif light.png");
		Sprite* s2 = Sprite::getSprite("theif shadow.png");
		m_shader->addImage(s1->textureID, "imageLight");
		m_shader->addImage(s2->textureID, "imageShadow");
	}

	m_shader->enable();
	m_shader->setColor(color);

	m_shader->addImage(sprite->textureID, "image");
	m_shader->setImage(sprite->textureID);

	const GLuint texLoc = m_shader->getAttribLocation("texCoord");
	const GLuint screenPosLoc = m_shader->getAttribLocation("screenPos");
	const GLuint worldPosLoc = m_shader->getAttribLocation("worldPos");

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

	m_shader->disable();
}

