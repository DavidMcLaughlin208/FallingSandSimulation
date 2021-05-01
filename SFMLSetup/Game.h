#pragma once

#include <iostream>
#include <vector>
#include "UnitUtils.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <chrono>
#include <vector>
#include "CellularMatrix.h"

class Game
{
private:
	//Private Variables
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Vector2i mousePosWindow;
	float enemySpawnTimer;
	UnitUtils* unitUtils;
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 800;
	int pixelModifier = 2;
	sf::Texture* texture;
	sf::Sprite* sprite;
	std::vector<sf::Uint8>* pixels;
	CellularMatrix* matrix;

	//GameObjects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::VertexArray* va;


	//Private Functions
	void initializeVariables();
	void initWindow();
	void initGL();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	const bool running();

	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void initTexture();
	void initVertexArray();

	void shuffleVertArray();

	void update();
	void updateTexture();
	void render();
	void renderEnemies();
};

