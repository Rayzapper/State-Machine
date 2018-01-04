#ifndef RAYZAPPER_UNIT_H
#define RAYZAPPER_UNIT_H

#include "GameObject.h"

class Unit : public GameObject
{
public:
	virtual void Render(sf::RenderWindow *window);
	void Move();
	void Move(float speed);
	float GetSpeed();
	float GetFacing();
	float GetFear();
	virtual void SetPosition(sf::Vector2f position);
	void SetFacing(float facing);
	void OffsetFacing(float offset);

	virtual bool IsWolf();
	virtual bool IsSheep();
protected:
	Unit();
	sf::CircleShape m_BodyShape, m_EyeShape1, m_EyeShape2;
	float m_Facing = 0.f, m_Speed = 0.f, m_FearDistance = 0.f;
};

class Wolf : public Unit
{
public:
	Wolf();
	virtual bool IsWolf();
private:

};

class Sheep : public Unit
{
public:
	Sheep();
	virtual bool IsSheep();
private:

};

#endif