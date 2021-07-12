#include "Simulation.h"
#include "RockPaperScissors.h"
#include "Life.h"

#include <thread>
#include <list>


struct cell {
	int cellType;
	int predatorType;
};

const bool Simulation::running()
{
	return this->window->isOpen();
}

void Simulation::initWindow()
{
	this->videoMode.height = this->windowHeight;
	this->videoMode.width = this->windowWidth;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Simulation::initializeVariables() {
	this->window = nullptr;
	this->unitUtils = new UnitUtils(this->pixelModifier, this->windowWidth, this->windowHeight);
	this->matrix = new CellularAutomaton(this->unitUtils->getMatrixWidth(), this->unitUtils->getMatrixHeight());
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	this->threadCount = this->unitUtils->getMatrixWidth() / 30;
	
	std::cout << this->threadCount << std::endl;
}

Simulation::Simulation(RuleSet* ruleSet_)
{
	srand(time(0));
	this->ruleSet = ruleSet_;
	this->ruleSet->sim = this;
	this->initializeVariables();
	this->initWindow();
	this->populateMatrix();
	this->initTexture();


	
	
	shader.loadFromFile("frag.glsl", sf::Shader::Fragment);
	if (!shader.isAvailable()) {
		std::cout << "The shader is not available\n";
	}
	shader.setUniform("resolution", sf::Vector2f(this->windowWidth, this->windowHeight));
}

Simulation::~Simulation()
{
}

void Simulation::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		case sf::Event::MouseButtonPressed:
			mouseDown = true;
			break;
		case sf::Event::MouseButtonReleased:
			mouseDown = false;
			break;
		default:
			break;
		}
	}

	if (mouseDown) {
		//click();
	}
}

void Simulation::click() {
	int mouseMatrixX = this->unitUtils->convertToMatrix(this->mousePosWindow.x);
	int mouseMatrixY = this->unitUtils->getMatrixHeight() - this->unitUtils->convertToMatrix(this->mousePosWindow.y);
	int brushSize = 7;
	for (int modY = -brushSize; modY <= brushSize; modY++) {
		for (int modX = -brushSize; modX <= brushSize; modX++) {
			if (mouseMatrixX + modX < 0 || mouseMatrixX + modX > this->unitUtils->getMatrixWidth() - 1 || mouseMatrixY + modY < 0 || mouseMatrixY + modY > this->unitUtils->getMatrixHeight() - 1) {
				continue;
			}
			this->matrix->setCell(mouseMatrixX + modX, mouseMatrixY + modY, rand() % this->cellTypes);
		}
	}
}

void Simulation::populateMatrix() {
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	/*int borders = totalCellsPerRow / (this->cellTypes - 1);
	int borders2 = totalRows / (this->cellTypes - 1);*/
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = 0; x < totalCellsPerRow; x++) {
			this->matrix->setCell(x + y * totalCellsPerRow, this->ruleSet->populateInitalCell(x, y));
		}
	}
	this->matrix->swapBuffer();
	std::cout << "Finished populating matrix" << std::endl;
}

//void Simulation::updateMatrix() {
//	int totalRows = this->unitUtils->getMatrixHeight();
//	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
//	for (int y = 0; y < totalRows; y++) {
//		//std::cout << "newRow" << y << std::endl;
//		for (int x = 0; x < totalCellsPerRow; x++) {
//			int currentCell = this->matrix->getCell(x + y * totalCellsPerRow);
//			bool getEaten = getNeighbors(x, y, currentCell);
//			if (getEaten) {
//				if (currentCell == 0) {
//					this->matrix->setCell(x + y * totalCellsPerRow, 3);
//				}
//				else {
//					this->matrix->setCell(x + y * totalCellsPerRow, currentCell - 1);
//				}
//				
//			}
//			else {
//				this->matrix->setCell(x + y * totalCellsPerRow, currentCell);
//			}
//			
//		}
//	}
//}

void Simulation::updateMatrixColumn(int start, int end) {
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = start; x <= end; x++) {
			if (x > this->unitUtils->getMatrixWidth()) {
				continue;
			}
			int currentCell = this->matrix->getCell(x + y * totalCellsPerRow);
			//int convertedCellType = getNeighbors(x, y, currentCell);
			int convertedCellType = this->ruleSet->processCell(x, y, currentCell);
			this->matrix->setCell(x + y * totalCellsPerRow, convertedCellType);

		}
	}
}

void Simulation::initTexture() {
	this->texture->create(unitUtils->getMatrixWidth(), unitUtils->getMatrixHeight());
	this->pixels = new std::vector<sf::Uint8>(this->unitUtils->getMatrixWidth() * this->unitUtils->getMatrixHeight() * this->unitUtils->getPixelSize());
	this->updateTexture();
	this->sprite->setTexture(*this->texture);
	this->sprite->setScale(this->unitUtils->getPixelModifier(), this->unitUtils->getPixelModifier());
}

void Simulation::updateTexture() {
	std::vector<sf::Uint8> pixelRef = *this->pixels;
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	for (int y = 0; y < totalRows; y++) {
		for (int x = 0; x < totalCellsPerRow; x++) {
			int actualX = x * this->unitUtils->getPixelSize();
			int actualY = y * totalCellsPerRow * this->unitUtils->getPixelSize();
			int cellType = this->matrix->getCell(x + y * totalCellsPerRow);
			sf::Color color = this->ruleSet->getColorForCell(cellType);
			pixelRef[actualX + actualY] = color.r;
			pixelRef[actualX + actualY + 1] = color.g;
			pixelRef[actualX + actualY + 2] = color.b;
			pixelRef[actualX + actualY + 3] = color.a;
		}
	}
	sf::Uint8* startOfArray = &pixelRef[0];
	this->texture->update(startOfArray);
}

void Simulation::updateTextureColumn(int start, int end) {
	std::vector<sf::Uint8> pixelRef = *this->pixels;
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	for (int y = 0; y < totalRows; y++) {
		for (int x = start; x <= end; x++) {
			int actualX = x * this->unitUtils->getPixelSize();
			int actualY = y * totalCellsPerRow * this->unitUtils->getPixelSize();
			int cellType = this->matrix->getCell(x + y * totalCellsPerRow);
			sf::Color color;
			if (cellType == 0) {
				color = sf::Color::Blue;
			}
			else if (cellType == 1) {
				color = sf::Color::Magenta;
			}
			else if (cellType == 2) {
				color = sf::Color::Yellow;
			}
			pixelRef[actualX + actualY] = color.r;
			pixelRef[actualX + actualY + 1] = color.g;
			pixelRef[actualX + actualY + 2] = color.b;
			pixelRef[actualX + actualY + 3] = color.a;
		}
	}
	//sf::Uint8* startOfArray = &pixelRef[0];
	//this->texture->update(startOfArray);
}

void Simulation::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Simulation::update()
{
	this->updateMousePositions();
	
	if (this->threads) {
		std::list <std::thread> threadList;
		int spanForColumn = this->unitUtils->getMatrixWidth() / this->threadCount;
		for (int t = 0; t < this->threadCount - 1; t++) {
			threadList.push_back(std::thread(&Simulation::updateMatrixColumn, this, t * spanForColumn, t * spanForColumn + spanForColumn - 1));
		}
		threadList.push_back(std::thread(&Simulation::updateMatrixColumn, this, (this->threadCount - 1) * spanForColumn, this->unitUtils->getMatrixWidth() - 1));
		std::list<std::thread>::iterator it;
		for (it = threadList.begin(); it != threadList.end(); ++it) {
			it->join();
		}
		this->updateTexture();
		/*threadList.clear();
		for (int t = 0; t < this->threadCount - 1; t++) {
			threadList.push_back(std::thread(&Simulation::updateTextureColumn, this, t * spanForColumn, t * spanForColumn + spanForColumn - 1));
		}
		threadList.push_back(std::thread(&Simulation::updateTextureColumn, this, (this->threadCount - 1) * spanForColumn, this->unitUtils->getMatrixWidth() - 1));
		std::list<std::thread>::iterator it2;
		for (it2 = threadList.begin(); it2 != threadList.end(); ++it2) {
			it2->join();
		}
		std::vector<sf::Uint8> pixelRef = *this->pixels;
		sf::Uint8* startOfArray = &pixelRef[0];
		this->texture->update(startOfArray);*/
	}
	else {
		/*this->updateMatrix();
		this->updateTexture();*/
	}

	


	this->pollEvents();

	this->matrix->swapBuffer();

	this->count++;
}

void Simulation::render()
{
	//this->window->draw(*this->sprite, &this->shader);
	this->window->draw(*this->sprite);
}


