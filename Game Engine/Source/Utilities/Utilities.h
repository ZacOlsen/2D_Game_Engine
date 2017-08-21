#pragma once

#include <FreeImage.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>

class Utilities {

public:

	static BYTE* loadImage(const char* filePath, unsigned int* width, unsigned int* height);
	static std::string readFile(const char* filePath);
	static void writeToFile(const char* filePath, std::string characters);

	static float randomFloatInRange(const float& low, const float& high);
	static int randomIntInRange(const int& low, const int& high);
};

