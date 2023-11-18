#pragma once
#ifndef BULLET_H
#define BULLET_H

#include<iostream>
#include<SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite shape;
	// this is pointer because you don't want to load the texture again
	// every time you run create a bullet
	//sf::Texture* texture; 

	sf::Vector2f direction;
	float movementSpeed;
public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	// Accessor
	const sf::FloatRect getBound() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !BULLET_H


