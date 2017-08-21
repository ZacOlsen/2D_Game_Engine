#include "Canvas.h"

string Canvas::getSaveString() {

	string save = "Canvas\n";
	return save;
}

void Canvas::renderUI() {
	renderIteration((RectTransform*)gameObject->transform);
}

void Canvas::renderIteration(RectTransform* rect) {

	Renderer* rend = rect->gameObject->getComponent<Renderer>();
	if (rend) {
		rend->render();
	}

	for (unsigned int i = 0; i < rect->childCount(); i++) {
		renderIteration(rect->getChild(i));
	}
}