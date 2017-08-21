#include "Button.h"

Button::Button(const Vector4& tintColor) {
	this->tintColor = tintColor;
}

string Button::getSaveString() {

	string save = "Button\n";
	save += to_string(tintColor.x) + ", " + to_string(tintColor.y) + ", " + to_string(tintColor.z)
		+ ", " + to_string(tintColor.w) + "\n";

	return save;
}

Button* Button::createFromString(const string& str) {

	Button* but = new Button();

	int start = 0;
	int end = str.find(',', start);
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
	but->tintColor = Vector4(xc, yc, zc, wc);

	return but;
}

void Button::start() {
	renderer = gameObject->getComponent<Renderer>();
}

void Button::update() {

	if (mouseInButton()) {

		if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
			tintRenderer();
			runPressCallbacks();

		} else if (Input::getMouseButtonReleased(GLFW_MOUSE_BUTTON_1)) {
			untintRenderer();
			runReleaseCallbacks();
		}

	} else {
		untintRenderer();
	}
}

void Button::addPressCallback(const std::function<void(void)>& func) {
	pressCallbacks.push_back(func);
}

void Button::addReleaseCallback(const std::function<void(void)>& func) {
	releaseCallbacks.push_back(func);
}

bool Button::mouseInButton() {

	Vector2 botL(-.5f, -.5f);
	Vector2 topR(.5f, .5f);
	Vector2 dontUse;

	Vector2 mousePos = gameObject->transform->parent->getTransformation() * Input::getMousePosition();
	gameObject->transform->getCameraPerspectivePosition(botL, topR, dontUse, dontUse);

	return mousePos.y <= topR.y && mousePos.y >= botL.y && mousePos.x >= botL.x && mousePos.x <= topR.x;
}

void Button::tintRenderer() {

	if (renderer) {
		renderer->color = tintColor;
	}
}

void Button::untintRenderer() {

	if (renderer) {
		renderer->color = Vector4(1, 1, 1, 1);
	}
}

void Button::runPressCallbacks() {
	for (unsigned int i = 0; i < pressCallbacks.size(); i++) {
		pressCallbacks[i]();
	}
}

void Button::runReleaseCallbacks() {
	for (unsigned int i = 0; i < releaseCallbacks.size(); i++) {
		releaseCallbacks[i]();
	}
}
