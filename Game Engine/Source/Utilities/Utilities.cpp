#include "Utilities.h"

BYTE* Utilities::loadImage(const char* filePath, unsigned int* width, unsigned int* height) {

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = NULL;
	fif = FreeImage_GetFileType(filePath, 0);
	if (fif == FIF_UNKNOWN) {
		fif = FreeImage_GetFIFFromFilename(filePath);
	}

	if (fif == FIF_UNKNOWN) {
		std::cout << "could load image: " << filePath << std::endl;
		return NULL;
	}

	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, filePath);
	}

	if (!dib) {
		std::cout << "could not read image: " << filePath << std::endl;
		return NULL;
	}

	dib = FreeImage_ConvertTo32Bits(dib);
	BYTE* result = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
	return result;
}

std::string Utilities::readFile(const char* filePath) {

	using namespace std;

	ifstream in(filePath);
	std::stringstream buffer;
	buffer << in.rdbuf();
	string result(buffer.str());
	in.close();

	return result;
}

void Utilities::writeToFile(const char* filePath, std::string characters) {

	using namespace std;

	ofstream out(filePath);
	out << characters;
	out.close();
}

float Utilities::randomFloatInRange(const float& low, const float& high) {
	return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));
}

int Utilities::randomIntInRange(const int& low, const int& high) {
	return low + rand() % (high - low + 1);
}
