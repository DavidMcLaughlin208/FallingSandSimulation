#include "CellularAutomaton.h"

#include <iostream>

CellularAutomaton::CellularAutomaton(int _width, int _height)
{
	this->width = _width;
	this->height = _height;
	this->matrix = new std::vector<int>(_width * _height);
	this->buffer = new std::vector<int>(_width * _height);
}

CellularAutomaton::~CellularAutomaton()
{
}

void CellularAutomaton::setCell(int index, int val)
{
	(*this->buffer)[index] = val;
}

void CellularAutomaton::setCell(int x, int y, int val)
{
	(*this->buffer)[x + y * this->width] = val;
}

int CellularAutomaton::getCell(int index)
{
	return (*this->matrix)[index];
}

void CellularAutomaton::swapBuffer() {
	std::vector<int>* bufferPointer = this->buffer;
	this->buffer = this->matrix;
	this->matrix = bufferPointer;
}
