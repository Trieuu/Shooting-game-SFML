#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600),"Marethyu3",sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTexture()
{
	this->texture["BULLET"] = new sf::Texture();
	this->texture["BULLET"]->loadFromFile("Texture/star 1.png");

	this->texture["Cat"] = new sf::Texture();
	this->texture["Cat"]->loadFromFile("Texture/star 2.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << " ! ERRPR::GAME::INITFONTS:: Can not load the file";
	}
	//This point text
	this->pointText.setPosition(700.f,25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(25);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x/2 - this->gameOverText.getGlobalBounds().width/2.f, 
		this->window->getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init playerGui
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(25.f, 25.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldTexture.loadFromFile("Texture/background.png")) {
		std::cout << " ! ERROR::GAME::INITTEXTURE::CAN'T LOAD THE FILE.\n";
	}
	this->worldBackGround.setTexture(this->worldTexture);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

// Constructor and Destructor
Game::Game()
{
	this->initWindow();
	this->initTexture();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initGUI();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete texture
	for (auto& i : this->texture) {
		delete i.second;
	}

	//Delete bullet
	for (auto *i : this->bullet) {
		delete i;
	}

	//Delete enemies
	for (auto* e : this->enemies) {
		delete e;
	}
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->updatePollEvent();
		if (this->player->getHp() > 0) {
			this->update();
			this->render();
		}
	}
}

void Game::updatePollEvent()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->window->close();
		}
		if (e.KeyPressed && e.key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->player->move(0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && this->player->canAttack()) {
		this->bullet.push_back(new Bullet(this->texture["BULLET"],this->player->getPos().x + 45.f, this->player->getPos().y + 75.f, 0.f, -1.f, 5.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && this->player->canAttack()) {
		this->bullet.push_back(new Bullet(this->texture["Cat"], this->player->getPos().x + 45.f, this->player->getPos().y + 75.f, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: "<<this->points;
	this->pointText.setString(ss.str());

	//Update player GUI
	
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f*hpPercent,this->playerHpBar.getSize().y));

}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f,this->player->getBounds().top);
	}
	else if (this->player->getBounds().left  + this->player->getBounds().width > this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left,0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullet()
{	
	for (int i = 0;i < this->bullet.size();i++) {
		this->bullet[i]->update();
		if (this->bullet[i]->getBound().top + this->bullet[i]->getBound().height < 0.f) {
			delete this->bullet.at(i); // The type of vector is pointer of type Bullet
			this->bullet.erase(this->bullet.begin() + i);
		}
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand()% this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	for (int i = 0;i < this->enemies.size();i++) {
		this->enemies[i]->update();
		// If get the bottom of the screen
		if (this->enemies[i]->getBounds().top > this->window->getSize().y) {
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		} // If intersect with the player
		else if (this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
			this->player->loseHp(this->enemies[i]->getDamage());

			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::updateCombat()
{
	for (int i = 0;i < this->enemies.size();i++) {
		bool enemy_deleted = false;
		for (int j = 0;j < this->bullet.size() && !enemy_deleted;j++) {
			if (this->enemies[i]->getBounds().intersects(this->bullet[j]->getBound())) {
				
				this->points += this->enemies[i]->getPoints();
				
				delete this->bullet[j];
				this->bullet.erase(this->bullet.begin() + j);

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);


				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullet();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackGround);
}

void Game::render()
{
	this->window->clear(); // clear old frame

	//Draw world
	this->renderWorld();

	//Draw all of the stuff here
	this->player->render(*this->window);
	for (auto* i : this->bullet) {
		i->render(this->window);
	}

	for (auto* e : enemies) {
		e->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
	}

	this->window->display(); // display the new frame
}
