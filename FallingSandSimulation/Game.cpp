#include "Game.h"
#include <Windows.h>
#include <GLEW/glew.h>
#include <SFML/Graphics.hpp>


void Game::initializeVariables()
{
	this->window = nullptr;
	this->unitUtils = new UnitUtils(this->pixelModifier, this->windowWidth, this->windowHeight);
	this->matrix = new CellularMatrix(this->unitUtils->convertToMatrix(this->windowWidth), this->unitUtils->convertToMatrix(this->windowHeight));
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	
}

void Game::initWindow()
{
	this->videoMode.height = this->windowHeight;
	this->videoMode.width = this->windowWidth;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initGL() {
	//glEnable(GL_TEXTURE_2D);
	//glShadeModel(GL_FLAT);
}

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initVertexArray();
	this->initTexture();
}
Game::~Game() {
	delete this->window;
	delete this->unitUtils;
	delete this->pixels;
}

const bool Game::running()
{
	return this->window->isOpen();
}

//Accessors

void Game::pollEvents()
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
			break;
		default:
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::initTexture() {
	this->texture->create(unitUtils->convertToMatrix(this->windowWidth), unitUtils->convertToMatrix(this->windowHeight));
	this->pixels = new std::vector<sf::Uint8>(this->unitUtils->convertToMatrix(this->windowWidth) * this->unitUtils->convertToMatrix(this->windowHeight) * this->unitUtils->getPixelSize());
	this->updateTexture();
}

void Game::updateTexture()
{
	std::vector<sf::Uint8> pixelRef = *this->pixels;
	int totalRows = this->unitUtils->convertToMatrix(this->unitUtils->getHeight());
	int totalCellsPerRow = this->unitUtils->convertToMatrix(this->unitUtils->getWidth());
	sf::Color currentColor;
	std::vector<sf::Color> colors;
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::Cyan);
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = 0; x < totalCellsPerRow; x++) {
			currentColor = colors[rand() % colors.size()];

			int actualX = x * this->unitUtils->getPixelSize();
			int actualY = y * totalCellsPerRow * this->unitUtils->getPixelSize();
			pixelRef[actualX + actualY] = currentColor.r;
			pixelRef[actualX + actualY + 1] = currentColor.g;
			pixelRef[actualX + actualY + 2] = currentColor.b;
			pixelRef[actualX + actualY + 3] = currentColor.a;
		}
	}
	this->sprite->setTexture(*this->texture);
	sf::Uint8* startOfArray = &pixelRef[0];
	this->texture->update(startOfArray);
	this->sprite->setScale(this->unitUtils->getPixelModifier(), this->unitUtils->getPixelModifier());
}

void Game::initVertexArray()
{
	srand(time(0));
	int totalRows = this->unitUtils->convertToMatrix(this->unitUtils->getHeight());
	int totalCellsPerRow = this->unitUtils->convertToMatrix(this->unitUtils->getWidth());
	this->va = new sf::VertexArray(sf::Quads, totalRows * totalCellsPerRow * 4);
	sf::Color currentColor;
	std::vector<sf::Color> colors;
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::Cyan);
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = 0; x < totalCellsPerRow; x++) {
			currentColor = colors[rand() % colors.size()];

			int actualX = x * this->unitUtils->getQuadSize();
			int actualY = y * totalCellsPerRow * this->unitUtils->getQuadSize();
			this->va->operator[](actualX + actualY).color = currentColor;
			this->va->operator[](actualX + actualY).position = sf::Vector2f(x * this->unitUtils->getPixelModifier(), this->unitUtils->convertToPixel(y));

			this->va->operator[](actualX + actualY + 1).color = currentColor;
			this->va->operator[](actualX + actualY + 1).position = sf::Vector2f((x + 1) * this->unitUtils->getPixelModifier(), this->unitUtils->convertToPixel(y));

			this->va->operator[](actualX + actualY + 2).color = currentColor;
			this->va->operator[](actualX + actualY + 2).position = sf::Vector2f((x + 1) * this->unitUtils->getPixelModifier(), this->unitUtils->convertToPixel(y) + this->unitUtils->getPixelModifier());

			this->va->operator[](actualX + actualY + 3).color = currentColor;
			this->va->operator[](actualX + actualY + 3).position = sf::Vector2f(x * this->unitUtils->getPixelModifier(), this->unitUtils->convertToPixel(y) + this->unitUtils->getPixelModifier());
		}
	}
}

void Game::shuffleVertArray() {
	int totalRows = unitUtils->getMatrixHeight();
	int totalCellsPerRow = unitUtils->getMatrixWidth();
	int quadSize = 4;
	sf::Color currentColor;
	std::vector<sf::Color> colors;
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::Cyan);
	for (int y = 0; y < totalRows; y++) {

		for (int x = 0; x < totalCellsPerRow; x++) {
			currentColor = colors[rand() % colors.size()];

			int actualX = x * quadSize;
			int actualY = y * totalCellsPerRow * quadSize;
			this->va->operator[](actualX + actualY).color = currentColor;
			this->va->operator[](actualX + actualY + 1).color = currentColor;
			this->va->operator[](actualX + actualY + 2).color = currentColor;
			this->va->operator[](actualX + actualY + 3).color = currentColor;
		}
	}
}

void Game::update()
{
	this->updateMousePositions();

	this->pollEvents();

	//this->shuffleVertArray();

	//this->updateTexture();

}

void Game::render()
{
	this->window->clear();

	//this->window->draw(*this->va);

	this->window->draw(*this->sprite);

	this->window->display();
}
