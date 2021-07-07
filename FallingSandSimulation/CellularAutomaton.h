#pragma once
#include <vector>
class CellularAutomaton
{

private:
	std::vector<int>* matrix;
	std::vector<int>* buffer;
	int width;
	int height;

public:
	CellularAutomaton(int _width, int _height);
	~CellularAutomaton();
	void setCell(int index, int val);
	void setCell(int x, int y, int val);
	int getCell(int index);
	void swapBuffer();
};

