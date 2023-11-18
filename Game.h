#pragma once
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

#include<string>
#include<sstream>
#include<map>
#include<vector>

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resource
	// This help to easy access thing without create enumeration.
	// One more thing is that, we set the texture as pointer
	// because we don't want it is a copy, instead we want it is actual texture.
	std::map<std::string,sf::Texture*> texture;
	std::vector<Bullet*> bullet;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Texture worldTexture;
	sf::Sprite worldBackGround;

	//Systems
	unsigned points;

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemy
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private function
	void initWindow();
	void initTexture();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvent();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullet();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderGUI();
	void renderWorld();
	void render();
};

