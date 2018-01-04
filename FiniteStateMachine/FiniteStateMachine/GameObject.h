#ifndef	RAYZAPPER_GAMEOBJECT_H
#define RAYZAPPER_GAMEOBJECT_H

#include <SFML\Graphics.hpp>

#define PI 3.1415926

class GameObject
{
public:
	virtual void Render(sf::RenderWindow *window) = 0;
	virtual void SetPosition(sf::Vector2f position) = 0;
	virtual sf::Vector2f GetPosition();
protected:
	GameObject();
	sf::Vector2f m_Position = sf::Vector2f(0.f, 0.f);
};

#endif