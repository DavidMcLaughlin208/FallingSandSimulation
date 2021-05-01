#pragma once
#include <vector>
#include "Element.h"

class Element;

class CellularMatrix
{
private:
	std::vector<Element*>* matrix;
	int width;
	int height;
public:
	CellularMatrix(int _width, int _height);
	~CellularMatrix();

	Element* get(int x, int y);

	void setElementAtIndex(int x, int y, Element* element);
	//void spawnElementAtIndex(int x, int y, )

};

