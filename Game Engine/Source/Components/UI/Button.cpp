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

const bool Button::mouseInButton() const {

	Vector2 botL(-.5f, -.5f);
	Vector2 topR(.5f, .5f);
	Vector2 dontUse;

	Vector2 mousePos = Input::getMousePosition();

	if (GameManager::canvas->scaleWithScreenSize) {
		Vector2 scale = gameObject->transform->getRoot()->getLocalScale();
		Vector2 camScale = Vector2(2.0f / (float)Camera::getWidth(), 2.0f / (float)Camera::getHeight());

		if (scale != camScale) {
			mousePos.x *= camScale.x / scale.x;
			mousePos.y *= camScale.y / scale.y;
		}
	}

	mousePos = gameObject->transform->getRoot()->getTransformation() * mousePos;
	gameObject->transform->getCameraPerspectivePosition(botL, topR, dontUse, dontUse);

	return mousePos.y <= topR.y && mousePos.y >= botL.y && mousePos.x >= botL.x && mousePos.x <= topR.x;
}

void Button::tintRenderer() const {

	if (renderer) {
		renderer->color = tintColor;
	}
}

void Button::untintRenderer() const {

	if (renderer) {
		renderer->color = Vector4(1, 1, 1, 1);
	}
}

void Button::runPressCallbacks() const {
	for (unsigned int i = 0; i < pressCallbacks.size(); i++) {
		pressCallbacks[i]();
	}
}

void Button::runReleaseCallbacks() const {
	for (unsigned int i = 0; i < releaseCallbacks.size(); i++) {
		releaseCallbacks[i]();
	}
}
