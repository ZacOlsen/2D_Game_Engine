#include "Canvas.h"

string Canvas::getSaveString() {

	string save = "Canvas\n";
	return save;
}

void Canvas::renderUI() const {
	renderIteration((RectTransform*)gameObject->transform);
}

void Canvas::renderIteration(const RectTransform* rect) const {

	Renderer* rend = rect->gameObject->getComponent<Renderer>();
	if (rend) {
		rend->render();
	}

	for (unsigned int i = 0; i < rect->childCount(); i++) {
		renderIteration(rect->getChild(i));
	}
}