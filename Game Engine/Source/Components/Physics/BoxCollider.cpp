#include "BoxCollider.h"

unsigned short BoxCollider::counter;

BoxCollider::BoxCollider(const Vector2& size, const bool& trigger) : id(counter++) {

	this->size = size;
	this->trigger = trigger;

	Physics::addCollider(this);
}

BoxCollider::~BoxCollider() {
	Physics::removeCollider(this);
}

BoxCollider* BoxCollider::createFromString(const string& str) {

	BoxCollider* box = new BoxCollider();

	int start = 0;
	int end = str.find('\n', start);
	bool trig = std::stoi(str.substr(start, end - start));
	box->trigger = trig;

	start = end + 1;
	end = str.find(',', start);
	float xs = std::stof(str.substr(start, end - start));

	start = end + 2;
	end = str.find('\n', start);
	float ys = std::stof(str.substr(start, end - start));
	box->size = Vector2(xs, ys);

	return box;
}

std::string BoxCollider::getSaveString() {

	string save = "BoxCollider\n";
	save += to_string(trigger) + "\n";
	save += to_string(size.x) + ", " + to_string(size.y) + "\n";

	return save;
}

float BoxCollider::checkVerticalCollision(const float& distance, BoxCollider& other) {

	const Vector2 pos = gameObject->transform->getWorldPosition();
	const Vector2 oPos = other.gameObject->transform->getWorldPosition();

	float top = pos.y + size.y / 2.0f + distance;
	float bot = pos.y - size.y / 2.0f + distance;
	float right = pos.x + size.x / 2.0f;
	float left = pos.x - size.x / 2.0f;

	float oTop = oPos.y + other.size.y / 2.0f;
	float oBot = oPos.y - other.size.y / 2.0f;
	float oRight = oPos.x + other.size.x / 2.0f;
	float oLeft = oPos.x - other.size.x / 2.0f;

	if (top <= oBot) {
		return distance;
	}

	if (bot >= oTop) {
		return distance;
	}

	if (right <= oLeft) {
		return distance;
	}

	if (left >= oRight) {
		return distance;
	}

	if (distance < 0) {
		return distance - (bot - oTop);
	} else {
		return distance - (top - oBot);
	}
}

float BoxCollider::checkHorizontalCollision(const float& distance, BoxCollider& other) {
	
	const Vector2 pos = gameObject->transform->getWorldPosition();
	const Vector2 oPos = other.gameObject->transform->getWorldPosition();

	float top = pos.y + size.y / 2.0f;
	float bot = pos.y - size.y / 2.0f;
	float right = pos.x + size.x / 2.0f + distance;
	float left = pos.x - size.x / 2.0f + distance;

	float oTop = oPos.y + other.size.y / 2.0f;
	float oBot = oPos.y - other.size.y / 2.0f;
	float oRight = oPos.x + other.size.x / 2.0f;
	float oLeft = oPos.x - other.size.x / 2.0f;

	if (top <= oBot + PHYSICS_EPSILON) {
		return distance;
	}

	if (bot >= oTop - PHYSICS_EPSILON) {
		return distance;
	}

	if (right <= oLeft) {
		return distance;
	}

	if (left >= oRight) {
		return distance;
	}

	if (distance <= 0) {
		return distance - (left - oRight);
	} else {
		return distance - (right - oLeft);
	}
}

bool BoxCollider::checkPointCollision(const float& x, const float& y) {
	
	const Vector2 pos = gameObject->transform->getWorldPosition();
	
	float top = pos.y + size.y / 2.0f;
	float bot = pos.y - size.y / 2.0f;
	float right = pos.x + size.x / 2.0f;
	float left = pos.x - size.x / 2.0f;

	return x < right && x > left && y < top && y > bot;
}

float BoxCollider::checkLineCollision(const Vector2& origin, const Vector2& end) {

	if (checkPointCollision(origin.x, origin.y)) {
		return 0;
	}

	if (origin == end) {
		return -1;
	}

	const Vector2 pos = gameObject->transform->getWorldPosition();

	float top = pos.y + size.y / 2.0f;
	float bot = pos.y - size.y / 2.0f;
	float right = pos.x + size.x / 2.0f;
	float left = pos.x - size.x / 2.0f;

	Vector2 corners[NUM_OF_CORNERS];
	corners[0] = Vector2(left, bot);
	corners[1] = Vector2(right, bot);
	corners[2] = Vector2(right, top);
	corners[3] = Vector2(left, top);;

	float shortestParamDist = FLT_MAX;

	//use for each box line
	// [E] _ [A B][t]
	// [F] - [C D][p]
	//which means
	// t = (ED - FB) / (AD - CB)
	// p = (AF - CE) / (AD - CB)

	//corners[i] is boxLineOrigin, corners[i+1] is boxLineEnd
	for (unsigned int i = 0; i < NUM_OF_CORNERS; i++) {

		Vector2 cornerEnd = i >= NUM_OF_CORNERS ? corners[0] : corners[i + 1];

		float e = origin.x - corners[i].x;
		float f = origin.y - corners[i].y;

		float a = cornerEnd.x - corners[i].x;
		float b = origin.x - end.x;
		float c = cornerEnd.y - corners[i].y;
		float d = origin.y - end.y;

		float divisor = a * d - c * b;
		//parallel case, is auto solved by box
		if (divisor == 0) {
			//if ((origin - corners[i]) * (cornerEnd - corners[i]) == 0) {
			//}	
			continue;
		}

		float t = (e * d - f * b) / divisor;
		float p = (a * f - c * e) / divisor;

		if (t >= 0 && t <= 1 && p >= 0 && p <= 1) {
			if (p < shortestParamDist) {
				shortestParamDist = p;
			}
		}
	}

	return shortestParamDist == FLT_MAX ? -1 : (end - origin).magnitude() * shortestParamDist; 
}

CollisionType BoxCollider::checkCollision(BoxCollider& other) {

	bool found = false;
	for (unsigned int i = 0; i < collidingIDs.size(); i++) {
		if (collidingIDs[i] == other.id) {
			found = true;
		}
	}

	const Vector2 pos = gameObject->transform->getWorldPosition();
	const Vector2 oPos = other.gameObject->transform->getWorldPosition();

	float top = pos.y + size.y / 2.0f;
	float bot = pos.y - size.y / 2.0f;
	float right = pos.x + size.x / 2.0f;
	float left = pos.x - size.x / 2.0f;

	float oTop = oPos.y + other.size.y / 2.0f;
	float oBot = oPos.y - other.size.y / 2.0f;
	float oRight = oPos.x + other.size.x / 2.0f;
	float oLeft = oPos.x - other.size.x / 2.0f;

	CollisionType colType = NONE;

	if (found) {
		colType = EXIT;
	}

	if (top < oBot - PHYSICS_EPSILON) {

		if (colType == EXIT) {
			removeCollisionID(other);
		}
		return colType;
	}

	if (bot > oTop + PHYSICS_EPSILON) {
		if (colType == EXIT) {
			removeCollisionID(other);
		}	
		return colType;
	}

	if (right < oLeft - PHYSICS_EPSILON) {
		if (colType == EXIT) {
			removeCollisionID(other);
		}	
		return colType;
	}

	if (left > oRight + PHYSICS_EPSILON) {
		if (colType == EXIT) {
			removeCollisionID(other);
		}
		return colType;
	}

	if (found) {
		colType = STAY;
	} else {
		colType = ENTER;
		collidingIDs.push_back(other.id);
		other.collidingIDs.push_back(id);
	}

	return colType;
}

void BoxCollider::removeCollisionID(BoxCollider& other) {

	auto it = find(collidingIDs.begin(), collidingIDs.end(), other.id);
	if (it != collidingIDs.end()) {
		swap(*it, collidingIDs.back());
		collidingIDs.pop_back();
	}

	it = find(other.collidingIDs.begin(), other.collidingIDs.end(), id);
	if (it != other.collidingIDs.end()) {
		swap(*it, other.collidingIDs.back());
		other.collidingIDs.pop_back();
	}
}

void BoxCollider::fixCollision(const BoxCollider& other) {

	const Vector2 pos = gameObject->transform->getWorldPosition();
	const Vector2 otherPos = other.gameObject->transform->getWorldPosition();
	const Vector2 previousPos = rb->getPreviousPosition();

	float top = pos.y + size.y / 2.0f;
	float bot = pos.y - size.y / 2.0f;
	float right = pos.x + size.x / 2.0f;
	float left = pos.x - size.x / 2.0f;

	float otherTop = otherPos.y + other.size.y / 2.0f;
	float otherBot = otherPos.y - other.size.y / 2.0f;
	float otherRight = otherPos.x + other.size.x / 2.0f;
	float otherLeft = otherPos.x - other.size.x / 2.0f;

	float oldTop = previousPos.y + size.y / 2.0f;
	float oldBot = previousPos.y - size.y / 2.0f;
	float oldRight = previousPos.x + size.x / 2.0f;
	float oldLeft = previousPos.x - size.x / 2.0f;

	//bot
	if (oldBot >= otherTop && bot < otherTop) {
		gameObject->transform->addToLocalPosition(0, -(bot - otherTop));
		rb->velocity.y = 0;
		rb->acceleration.y = 0;
		return;
	}

	//left
	if (oldLeft >= otherRight && left < otherRight) {
		gameObject->transform->addToLocalPosition(-(left - otherRight), 0);
		rb->velocity.x = 0;
		rb->acceleration.x = 0;
		return;
	}

	//right
	if (oldRight <= otherLeft && right > otherLeft) {
		gameObject->transform->addToLocalPosition(-(right - otherLeft), 0);
		rb->velocity.x = 0;
		rb->acceleration.x = 0;
		return;
	}

	//top
	if (oldTop <= otherBot && top > otherBot) {
		gameObject->transform->addToLocalPosition(0, -(top - otherBot));
		rb->velocity.y = 0;
		rb->acceleration.y = 0;
		return;
	}
}

ostream& operator<<(ostream& stream, const BoxCollider& box) {

	Vector2 pos = box.gameObject->transform->getWorldPosition();

	float top = pos.y + box.size.y / 2.0f;
	float bot = pos.y - box.size.y / 2.0f;
	float right = pos.x + box.size.x / 2.0f;
	float left = pos.x - box.size.x / 2.0f;

	stream << "BoxCollider:" << endl;
	stream << "Top " << top << endl;
	stream << "Bot " << bot << endl;
	stream << "Left " << left << endl;
	stream << "Right " << right << endl;

	RigidBody* rb = box.rb;

	if (rb) {
		Vector2 previous = rb->getPreviousPosition();
		top = previous.y + box.size.y / 2.0f;
		bot = previous.y - box.size.y / 2.0f;
		right = previous.x + box.size.x / 2.0f;
		left = previous.x - box.size.x / 2.0f;
	
		stream << "Previous:" << endl;
		stream << "Top " << top << endl;
		stream << "Bot " << bot << endl;
		stream << "Left " << left << endl;
		stream << "Right " << right << endl;
	}

	return stream;
}

void BoxCollider::renderBoxCollider() {

	float top = size.y / 2.0f;
	float bot = -size.y / 2.0f;
	float right = size.x / 2.0f;
	float left = -size.x / 2.0f;

	Vector2 topR = Vector2(right, top);
	Vector2 topL = Vector2(left, top);
	Vector2 botL = Vector2(left, bot);
	Vector2 botR = Vector2(right, bot);

	gameObject->transform->getCameraPerspectivePosition(topR, topL, botL, botR);

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 0);
	glVertex2f(topR.x, topR.y);
	glVertex2f(topL.x, topL.y);
	glVertex2f(botL.x, botL.y);
	glVertex2f(botR.x, botR.y);
	glEnd();
}