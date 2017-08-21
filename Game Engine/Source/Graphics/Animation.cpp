#include "Animation.h"

Animation::Animation(const vector<Sprite*> sprites, const float& frameRate, const char* name) {

	this->sprites = sprites;
	this->frameRate = frameRate;
	this->name = name;
}

string Animation::getSaveString() {

	string save = "Animation\n";
	save += string(name) + "\n";
	save += to_string(frameRate) + "\n";

	for (unsigned int i = 0; i < sprites.size(); i++) {
		save += sprites[i]->getFilePath();

		if (i < sprites.size() - 1) {
			save += ", ";
		}
	}

	save += "\n";
	return save;
}

Animation* Animation::createFromString(const string& str) {

	int start = 0;
	int end = str.find('\n', start);
	string name = str.substr(start, end - start);

	start = end + 1;
	end = str.find('\n', start);
	float frameRate = std::stof(str.substr(start, end - start));

	vector<Sprite*> sprites;
	start = end + 1;
	end = str.find(',', start);
	while (end > 0) {
		string spriteName = str.substr(start, end - start);
		char* c = new char[spriteName.length()];
		strcpy(c, spriteName.c_str());
		sprites.push_back(Sprite::getSprite(c));
		start = end + 2;
		end = str.find(',', start);
	}

	end = str.find('\n', start);
	string spriteName = str.substr(start, end - start);
	char* c = new char[spriteName.length()];
	strcpy(c, spriteName.c_str());
	sprites.push_back(Sprite::getSprite(c));

	c = new char[name.length()];
	strcpy(c, name.c_str());
	return new Animation(sprites, frameRate, c);
}

const unsigned int Animation::spriteCount() {
	return sprites.size();
}

Sprite*& Animation::getSprite(const unsigned int& index) {
	return sprites[index];
}
