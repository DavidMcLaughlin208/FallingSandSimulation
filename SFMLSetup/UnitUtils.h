#pragma once
class UnitUtils
{
private:
	int pixelModifier;
	int windowWidth;
	int windowHeight;
public:

	UnitUtils(int _pixelModifier, int _windowWidth, int _windowHeight);

	int convertToMatrix(int pixelValue);
	int convertToPixel(int matrixValue);

};

