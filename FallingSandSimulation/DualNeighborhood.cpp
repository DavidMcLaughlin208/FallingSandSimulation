#include "DualNeighborhood.h"
#include "Simulation.h"

DualNeighborhood::DualNeighborhood()
{
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
		int newY = y + modY;
		int newX1 = x - 2;
		int newX2 = x + 2;
		if (newY < 0) {
			newY += totalRows - 1;
		}
		if (newY > totalRows - 1) {
			newY -= totalRows - 1;
		} 
		if (newX1 < 0) {
			newX1 += totalCellsPerRow - 1;
		}
		if (newX2 > totalCellsPerRow - 1) {
			newX2 -= totalCellsPerRow - 1;
		}
		
		n2Total += RuleSet::sim->matrix->getCell(newX1 + newY * totalCellsPerRow);
		n2Total += RuleSet::sim->matrix->getCell(newX2 + newY * totalCellsPerRow);
	}
	for (int modX = -1; modX <= 1; modX++) {
		int newY1 = y - 2;
		int newY2 = y + 2;
		int newX = x + modX;
		
		if (newX < 0) {
			newX += totalCellsPerRow - 1;
		}
		if (newX > totalCellsPerRow - 1) {
			newX -= totalCellsPerRow - 1;
		}
		if (newY1 < 0) {
			newY1 += totalRows - 1;
		}
		if (newY2 > totalRows - 1) {
			newY2 -= totalRows - 1;
		}
		n2Total += RuleSet::sim->matrix->getCell(newX + newY1 * totalCellsPerRow);
		n2Total += RuleSet::sim->matrix->getCell(newX + newY2 * totalCellsPerRow);
	}

	if (cellType == 1) {
		if (n1Total <= 1 || n1Total >= 4) {
			if (n2Total < 6) {
				return 0;
			}
			return 0;
		}
	}
	else {
		if (n1Total == 3 || (n2Total < 10 && n2Total > 4)) {
			return 1;
		}
	}
	return cellType;
}

sf::Color DualNeighborhood::getColorForCell(int cellType)
{
	if (cellType == 1) {
		return sf::Color::Yellow;
	}
	else {
		return sf::Color::Black;
	}
}

int DualNeighborhood::populateInitalCell(int x, int y)
{
	return rand() % 2;
}
