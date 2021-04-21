#include "Game.h"
#include <Windows.h>
#include <GLEW/glew.h>
#include <SFML/Graphics.hpp>
#include <vector>


void Game::initializeVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = this->windowHeight;
	this->videoMode.width = this->windowWidth;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initGL() {
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);
}

void Game::initEnemies()  
{
	this->enemy.setPosition(10.0f, 10.0f);
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(0.5f, 0.5f);
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

Game::Game()
{
	this->unitUtils = new UnitUtils(this->pixelModifier, this->windowWidth, this->windowHeight);
	this->initializeVariables();
	this->initWindow();
	this->initEnemies();
	this->initVertexArray();
}
Game::~Game() {
	delete this->window;
	delete this->unitUtils;
}

const bool Game::running()
{
	return this->window->isOpen();
}

//Accessors

void Game::spawnEnemy()
{
}

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
		default:
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
}

void Game::initVertexArray()
{
	int totalCells = 10;
	this->va = new sf::VertexArray(sf::Quads, totalCells * 12);
	int quadSize = 4;
	sf::Color currentColor;
	std::vector<sf::Color> colors;
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Green);
	for (int x = 0; x <= totalCells; x++) {
		currentColor = colors[rand() % colors.size()];

		int actualX = x * quadSize;
		this->va->operator[](actualX).color = currentColor;
		this->va->operator[](actualX).position = sf::Vector2f(x * 10, 0);
		
		this->va->operator[](actualX + 1).color = currentColor;
		this->va->operator[](actualX + 1).position = sf::Vector2f((x + 1) * 10, 0);
		
		this->va->operator[](actualX + 2).color = currentColor;
		this->va->operator[](actualX + 2).position = sf::Vector2f((x + 1) * 10, 10);
		
		this->va->operator[](actualX + 3).color = currentColor;
		this->va->operator[](actualX + 3).position = sf::Vector2f(x * 10, 10);
	}
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	std::cout << this->va->getVertexCount() << std::endl;

	this->updateEnemies();

}

void Game::render()
{
	this->window->clear();

	this->window->draw(*this->va);

	//this->window->draw(this->enemy);

	this->window->display();
}

void Game::renderEnemies()
{
}
