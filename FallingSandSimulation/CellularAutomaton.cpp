#include "CellularAutomaton.h"

CellularAutomaton::CellularAutomaton(int _width, int _height)
{
	this->width = _width;
	this->height = _height;
	this->matrix = new std::vector<int>(_width * _height);
}

CellularAutomaton::~CellularAutomaton()
{
}

void CellularAutomaton::setCell(int index, int val)
{
	(*this->matrix)[index] = val;
}

void CellularAutomaton::setCell(int x, int y, int val)
{
	(*this->matrix)[x + y * this->width] = val;
}

int CellularAutomaton::getCell(int index)
{
	return (*this->matrix)[index];
}
