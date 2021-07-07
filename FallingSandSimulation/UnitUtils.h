#pragma once
class UnitUtils
{
private:
	int pixelModifier;
	int windowWidth;
	int windowHeight;
	int matrixHeight;
	int matrixWidth;
	int quadSize;
	int pixelSize;
public:

	UnitUtils(int _pixelModifier, int _windowWidth, int _windowHeight);

	int convertToMatrix(int pixelValue);
	int convertToPixel(int matrixValue);
	int getWidth();
	int getHeight();
	int getPixelModifier();
	int getMatrixHeight();
	int getMatrixWidth();
	int getPixelSize();
	int getQuadSize();

};

