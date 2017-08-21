#pragma once

#include <functional>
#include "..\Updateable.h"
#include "..\..\Misc\GameObject.h"
#include "..\..\Utilities\Input.h"

class Button : public Updateable {

public:

	Vector4 tintColor;

	Button(const Vector4& tintColor = Vector4(.8f, .8f, .8f, .8f));
	
	string getSaveString();
	static Button* createFromString(const string& str);

	void start();
	void update();

	void addPressCallback(const std::function<void(void)>& func);
	void addReleaseCallback(const std::function<void(void)>& func);

private:

	Renderer* renderer = nullptr;
	vector<std::function<void(void)>> pressCallbacks;
	vector<std::function<void(void)>> releaseCallbacks;

	bool mouseInButton();
	void tintRenderer();
	void untintRenderer();

	void runPressCallbacks();
	void runReleaseCallbacks();
};

