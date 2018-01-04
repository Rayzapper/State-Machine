#ifndef RAYZAPPER_GAME_H
#define RAYZAPPER_GAME_H

#include <SFML\Graphics.hpp>
#include "UnitBehavior.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Update(float dt, sf::Vector2i mousePosition);
	void Render();

	vector<UnitBehavior*> m_Units;

	sf::RenderWindow *m_Window;
};

#endif