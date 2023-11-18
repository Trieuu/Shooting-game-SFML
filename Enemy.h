#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int point;

	void initVariables();
	void initShape();
public:
	Enemy(float posX, float posY);
	virtual ~Enemy();
	//Accessor

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Function
	void update();
	void render(sf::RenderTarget* target);

};

#endif //!ENEMY_H