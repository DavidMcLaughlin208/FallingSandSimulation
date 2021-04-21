#include "UnitUtils.h"

UnitUtils::UnitUtils(int _pixelModifier, int _windowWidth, int _windowHeight) {
	this->pixelModifier = _pixelModifier;
	this->windowWidth = _windowWidth;
	this->windowHeight = _windowHeight;
}

int UnitUtils::convertToMatrix(int pixelValue)
{
	return pixelValue / pixelModifier;
}

int UnitUtils::convertToPixel(int matrixValue)
{
	return matrixValue * pixelModifier;
}
