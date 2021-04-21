#pragma once

#include <iostream>
#include <vector>
#include "UnitUtils.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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
	int windowWidth = 800;
	int windowHeight = 600;
	int pixelModifier = 2;

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
	void initVertexArray();

	void update();
	void render();
	void renderEnemies();
};

