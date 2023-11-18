#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; // 3->10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount/3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->point = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));

}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{

}

//Accessor

const sf::FloatRect Enemy::getBounds() const{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	// TODO: insert return statement here
	return this->point;
}

const int& Enemy::getDamage() const
{
	// TODO: insert return statement here
	return this->damage;
}

//Functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}


void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

