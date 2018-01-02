#ifndef RAYZAPPER_GAME_H
#define RAYZAPPER_GAME_H

#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Update(float dt, sf::Vector2i mousePosition);
	void Render();

	sf::RenderWindow *m_Window;
};

#endif