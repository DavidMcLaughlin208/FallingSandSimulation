#include "CellularMatrix.h"


CellularMatrix::CellularMatrix(int _width, int _height) {
	this->width = _width;
	this->height = _height;
	this->matrix = new std::vector<Element*>(_width * _height);
}

CellularMatrix::~CellularMatrix() {
	delete this->matrix;
}

Element* CellularMatrix::get(int x, int y)
{
	return (*this->matrix)[x + y * width];
}

void CellularMatrix::setElementAtIndex(int x, int y, Element* element) {
	(*this->matrix)[x + y * width] = element;
}
