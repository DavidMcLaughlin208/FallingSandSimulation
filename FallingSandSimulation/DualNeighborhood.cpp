#include "DualNeighborhood.h"
#include "Simulation.h"

DualNeighborhood::DualNeighborhood()
{
	on.r = 50;
	on.g = 50;
	on.b = 50;
}

int DualNeighborhood::processCell(int x, int y, int cellType)
{
	int totalRows = RuleSet::sim->unitUtils->getMatrixHeight();
	int totalCellsPerRow = RuleSet::sim->unitUtils->getMatrixWidth();
	int n1Total = 0;
	for (int modY = -1; modY <= 1; modY++) {
		for (int modX = -1; modX <= 1; modX++) {
			if (modY == 0 && modX == 0) {
				continue;
			}
			int newX = x + modX;
			int newY = y + modY;
			if (newX > totalCellsPerRow - 1) {
				newX = 0;
			}
			else if (newX < 0) {
				newX = totalCellsPerRow - 1;
			}

			if (newY > totalRows - 1) {
				newY = 0;
			}
			else if (newY < 0) {
				newY = totalRows - 1;
			}
			n1Total += RuleSet::sim->matrix->getCell(newX + newY * totalCellsPerRow);
		}
	}
	int n2Total = 0;
	for (int modY = -3; modY <= 3; modY++) {
		int newY = wrapYToBounds(y + modY);
		int newX1 = wrapXToBounds(x - 2);
		int newX2 = wrapXToBounds(x + 2);
		n2Total += RuleSet::sim->matrix->getCell(newX1 + newY * totalCellsPerRow);
		n2Total += RuleSet::sim->matrix->getCell(newX2 + newY * totalCellsPerRow);
	}
	for (int modX = -1; modX <= 1; modX++) {
		int newY1 = wrapYToBounds(y - 2);
		int newY2 = wrapYToBounds(y + 2);
		int newX = wrapXToBounds(x + modX);
		n2Total += RuleSet::sim->matrix->getCell(newX + newY1 * totalCellsPerRow);
		n2Total += RuleSet::sim->matrix->getCell(newX + newY2 * totalCellsPerRow);
	}
	int returnVal = 0;
	if (n1Total <= RuleSet::sliderVal1 || n1Total >= RuleSet::sliderVal2) { 
		returnVal = 0;
	}
	else {
		returnVal = 1;
	}
	if (n2Total <= RuleSet::sliderVal3 || n2Total >= RuleSet::sliderVal4) { 
		returnVal = 0;
	}
	return returnVal;
}

sf::Color DualNeighborhood::getColorForCell(int cellType)
{
	if (cellType == 1) {
		return on;
	}
	else {
		return sf::Color::Black;
	}
}

int DualNeighborhood::populateInitalCell(int x, int y)
{

	double noiseValue = RuleSet::sim->perlinNoise->noise((x / (double) RuleSet::sim->unitUtils->getMatrixWidth())*40, (y / (double)RuleSet::sim->unitUtils->getMatrixHeight())*40, 0.5);
	if (noiseValue > 0.5) {
		return 1;
	}
	else {
		return 0;
	}
	/*if (rand() % 4 == 0) {
		return 0;
	}
	else {
		return rand() % 2;
	}*/
}

int DualNeighborhood::wrapYToBounds(int val) {
	if (val < 0) {
		return val + (RuleSet::sim->unitUtils->getMatrixHeight() - 1);
	}
	if (val > RuleSet::sim->unitUtils->getMatrixHeight() - 1) {
		return val - (RuleSet::sim->unitUtils->getMatrixHeight() - 1);
	}

	return val;
}

int DualNeighborhood::wrapXToBounds(int val) {
	if (val < 0) {
		return val + (RuleSet::sim->unitUtils->getMatrixWidth() - 1);
	}
	if (val > RuleSet::sim->unitUtils->getMatrixWidth() - 1) {
		return val - (RuleSet::sim->unitUtils->getMatrixWidth() - 1);
	}
	return val;
}
