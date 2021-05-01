#pragma once

#include "CellularMatrix.h"

class CellularMatrix;

class Element
{
private:

public:
	virtual void step(CellularMatrix matrix) = 0;
};

