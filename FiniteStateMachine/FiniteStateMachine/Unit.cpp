#include "Unit.h"

void Unit::Render(sf::RenderWindow *window)
{
	window->draw(m_BodyShape);
	window->draw(m_EyeShape1);
	window->draw(m_EyeShape2);
}

void Unit::Move()
{
	sf::Vector2f newPosition = m_Position + sf::Vector2f(cosf(m_Facing) * m_Speed, sinf(m_Facing) * m_Speed);
	SetPosition(newPosition);
}

void Unit::Move(float speed)
{
	sf::Vector2f newPosition = m_Position + sf::Vector2f(cosf(m_Facing) * speed, sinf(m_Facing) * speed);
	SetPosition(newPosition);
}

float Unit::GetSpeed()
{
	return m_Speed;
}

float Unit::GetFacing()
{
	return m_Facing;
}

float Unit::GetFear()
{
	return m_FearDistance;
}

void Unit::SetPosition(sf::Vector2f position)
{
	m_Position = position;
	m_BodyShape.setPosition(position);
	m_EyeShape1.setPosition(position + sf::Vector2f(cosf(m_Facing - (PI / 12)) * 12, sinf(m_Facing - (PI / 12)) * 12));
	m_EyeShape2.setPosition(position + sf::Vector2f(cosf(m_Facing + (PI / 12)) * 12, sinf(m_Facing + (PI / 12)) * 12));
}

void Unit::SetFacing(float facing)
{
	m_Facing = facing;
	while (m_Facing >= PI * 2)
	{
		m_Facing -= PI * 2;
	}
	while (m_Facing < 0)
	{
		m_Facing += PI * 2;
	}
	SetPosition(m_BodyShape.getPosition());
}

void Unit::OffsetFacing(float offset)
{
	m_Facing += offset;
	while (m_Facing >= PI * 2)
	{
		m_Facing -= PI * 2;
	}
	while (m_Facing < 0)
	{
		m_Facing += PI * 2;
	}
	SetPosition(m_BodyShape.getPosition());
}

bool Unit::IsWolf()
{
	return false;
}

bool Unit::IsSheep()
{
	return false;
}

Unit::Unit()
{
	
}

Wolf::Wolf()
	: Unit()
{
	m_BodyShape.setRadius(20.f);
	m_BodyShape.setOrigin(m_BodyShape.getRadius(), m_BodyShape.getRadius());
	m_BodyShape.setFillColor(sf::Color(64, 64, 64, 255));
	m_EyeShape1.setRadius(2.f);
	m_EyeShape1.setFillColor(sf::Color::Yellow);
	m_EyeShape1.setOrigin(m_EyeShape1.getRadius(), m_EyeShape1.getRadius());
	m_EyeShape2 = m_EyeShape1;
	m_FearDistance = 200.f;

	m_Speed = 3.f;
}

bool Wolf::IsWolf()
{
	return true;
}

Sheep::Sheep()
	: Unit()
{
	m_BodyShape.setRadius(16.f);
	m_BodyShape.setOrigin(m_BodyShape.getRadius(), m_BodyShape.getRadius());
	m_BodyShape.setFillColor(sf::Color::White);
	m_EyeShape1.setRadius(3.f);
	m_EyeShape1.setFillColor(sf::Color::Black);
	m_EyeShape1.setOrigin(m_EyeShape1.getRadius(), m_EyeShape1.getRadius());
	m_EyeShape2 = m_EyeShape1;
	m_FearDistance = 300.f;

	m_Speed = 2.f;
}

bool Sheep::IsSheep()
{
	return true;
}