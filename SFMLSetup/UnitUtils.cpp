#include "UnitUtils.h"

UnitUtils::UnitUtils(int _pixelModifier, int _windowWidth, int _windowHeight) {
	this->pixelModifier = _pixelModifier;
	this->windowWidth = _windowWidth;
	this->windowHeight = _windowHeight;
	this->matrixHeight = _windowHeight / _pixelModifier;
	this->matrixWidth = _windowWidth / _pixelModifier;
}

int UnitUtils::convertToMatrix(int pixelValue)
{
	return pixelValue / pixelModifier;
}

int UnitUtils::convertToPixel(int matrixValue)
{
	return matrixValue * pixelModifier;
}

int UnitUtils::getWidth()
{
	return this->windowWidth;
}

int UnitUtils::getHeight()
{
	return this->windowHeight;
}

int UnitUtils::getPixelModifier()
{
	return this->pixelModifier;
}

int UnitUtils::getMatrixHeight()
{
	return this->matrixHeight;
}

int UnitUtils::getMatrixWidth()
{
	return this->matrixWidth;
}
