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
