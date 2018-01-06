#include "Game.h"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{
	for each (UnitBehavior *b in m_Units)
	{
		delete b;
	}
	m_Units.clear();
}

void Game::Run()
{
	int windowWidth = 900, windowHeight = 900;
	sf::Vector2i mouseScreenPosition;

	// Window creation
	sf::String programName = "StateMachineAI";
	m_Window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), programName, sf::Style::Default);
	m_Window->setFramerateLimit(60);
	m_Window->setVerticalSyncEnabled(true);

	sf::Clock deltaClock;

	float dt;

	bool running = true, focus = true;

	UnitBehavior *testWolf = new UnitBehavior(), *testWolf2 = new UnitBehavior(),
		*testWolf3 = new UnitBehavior(), *testWolf4 = new UnitBehavior(),
		*testWolf5 = new UnitBehavior(), *testWolf6 = new UnitBehavior(),
		*testWolf7 = new UnitBehavior(), *testWolf8 = new UnitBehavior(),
		*testSheep = new UnitBehavior(), *testSheep2 = new UnitBehavior(),
		*testSheep3 = new UnitBehavior(), *testSheep4 = new UnitBehavior();

	Unit *unit = new Wolf();
	unit->SetPosition(sf::Vector2f(30.f, 120.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(120.f, 30.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf2->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(780.f, 30.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf3->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(870.f, 120.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf4->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(870.f, 780.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf5->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(780.f, 870.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf6->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(120.f, 870.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf7->SetUnit(unit);

	unit = new Wolf();
	unit->SetPosition(sf::Vector2f(30.f, 780.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testWolf8->SetUnit(unit);

	unit = new Sheep();
	unit->SetPosition(sf::Vector2f(420.f, 420.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testSheep->SetUnit(unit);

	unit = new Sheep();
	unit->SetPosition(sf::Vector2f(480.f, 420.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testSheep2->SetUnit(unit);

	unit = new Sheep();
	unit->SetPosition(sf::Vector2f(420.f, 480.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testSheep3->SetUnit(unit);

	unit = new Sheep();
	unit->SetPosition(sf::Vector2f(480.f, 480.f));
	unit->SetFacing((PI / 32) * (rand() % 64));
	testSheep4->SetUnit(unit);

	m_Units.push_back(testWolf);
	m_Units.push_back(testWolf2);
	m_Units.push_back(testWolf3);
	m_Units.push_back(testWolf4);
	m_Units.push_back(testWolf5);
	m_Units.push_back(testWolf6);
	m_Units.push_back(testWolf7);
	m_Units.push_back(testWolf8);
	m_Units.push_back(testSheep);
	m_Units.push_back(testSheep2);
	m_Units.push_back(testSheep3);
	m_Units.push_back(testSheep4);

	while (running)
	{
		dt = deltaClock.restart().asSeconds();

		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			if (event.type == sf::Event::GainedFocus)
				focus = true;
			if (event.type == sf::Event::LostFocus)
				focus = false;
			if (event.type == sf::Event::Resized)
			{
				int newWidth = event.size.width, newHeight = event.size.height;
			}
		}

		if (focus)
		{
			mouseScreenPosition = sf::Mouse::getPosition(*m_Window);

			// --------------------Update--------------------

			Update(dt, mouseScreenPosition);

			// --------------------Render--------------------
			m_Window->clear(sf::Color(0, 200, 0, 255));
			Render();

			// End frame
			m_Window->display();
		}
		else
		{
			sf::Time time = sf::milliseconds(100);
			sf::sleep(time);

			mouseScreenPosition = sf::Mouse::getPosition(*m_Window);

			// --------------------Update--------------------

			Update(dt, mouseScreenPosition);

			// --------------------Render--------------------
			m_Window->clear(sf::Color(0, 200, 0, 255));
			Render();

			// End frame
			m_Window->display();
		}
	}
}

void Game::Update(float dt, sf::Vector2i mousePosition)
{
	bool mouseClick, rightClick;
	sf::Vector2f mouseWorldPosition = m_Window->mapPixelToCoords(mousePosition);

	vector<sf::Vector2f> wolfPositions;
	vector<UnitBehavior*> sheepVector;
	for each (UnitBehavior *b in m_Units)
	{
		if (b->GetUnit()->IsWolf())
			wolfPositions.push_back(b->GetUnit()->GetPosition());
		else
			sheepVector.push_back(b);
	}
	for each (UnitBehavior *b in m_Units)
	{
		float length;
		sf::Vector2f deltaVector;
		if (b->GetUnit()->IsWolf())
		{
			deltaVector = mouseWorldPosition - b->GetUnit()->GetPosition();
			length = sqrtf((deltaVector.x * deltaVector.x) + (deltaVector.y * deltaVector.y));
			if (length < b->GetUnit()->GetFear())
			{
				b->FleeMotion(mouseWorldPosition);
			}
		}
		else
		{
			vector<sf::Vector2f> fleeFromPositions;
			for each (sf::Vector2f v in wolfPositions)
			{
				deltaVector = v - b->GetUnit()->GetPosition();
				length = sqrtf((deltaVector.x * deltaVector.x) + (deltaVector.y * deltaVector.y));
				if (length < b->GetUnit()->GetFear())
				{
					fleeFromPositions.push_back(v);
				}
			}
			if (fleeFromPositions.size() > 0)
			{
				sf::Vector2f averageVector = sf::Vector2f(0.f, 0.f);
				for each (sf::Vector2f v in fleeFromPositions)
				{
					averageVector += v;
				}
				averageVector.x /= fleeFromPositions.size();
				averageVector.y /= fleeFromPositions.size();
				b->FleeMotion(averageVector);
			}
		}
		b->Update(dt, mousePosition, sheepVector);
		sf::Vector2f unitPos = b->GetUnit()->GetPosition();
		if (unitPos.x > 890.f)
			b->GetUnit()->SetPosition(sf::Vector2f(890.f, unitPos.y));
		else if (unitPos.x < 10.f)
			b->GetUnit()->SetPosition(sf::Vector2f(10.f, unitPos.y));
		if (unitPos.y > 890.f)
			b->GetUnit()->SetPosition(sf::Vector2f(unitPos.x, 890.f));
		else if (unitPos.y < 10.f)
			b->GetUnit()->SetPosition(sf::Vector2f(unitPos.x, 10.f));
	}
}

void Game::Render()
{
	for each (UnitBehavior *b in m_Units)
	{
		b->Render(m_Window);
	}
}