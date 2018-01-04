#include "UnitBehavior.h"
#include <iostream>

UnitBehavior::UnitBehavior()
{
	m_UnitState = new UnitState(nullptr, this);
}

UnitBehavior::~UnitBehavior()
{
	m_UnitState->Exit(true);
	delete m_UnitState;
	delete m_Unit;
}

void UnitBehavior::CreationPhase()
{
	m_UnitState->CreationPhase();
}

void UnitBehavior::AlivePhase()
{
	m_UnitState->AlivePhase();
}

void UnitBehavior::DestructionPhase()
{
	m_UnitState->DestructionPhase();
}

void UnitBehavior::DeadPhase()
{
	m_UnitState->DeadPhase();
}

void UnitBehavior::IdleMotion()
{
	int randomNr = rand() % 5;
	if (randomNr < 3)
		m_UnitState->StandIdleMotion();
	else if (randomNr < 4)
		m_UnitState->TurnIdleMotion();
	else
		m_UnitState->WalkIdleMotion();
}

void UnitBehavior::ChaseMotion(UnitBehavior *target)
{
	m_UnitState->ChaseMotion(target);
}

void UnitBehavior::FleeMotion(sf::Vector2f fleeFromPosition)
{
	float deltaAngle;
	sf::Vector2f deltaVector = fleeFromPosition - m_Unit->GetPosition();
	if (fleeFromPosition.y >= 0)
		deltaAngle = atan2f(deltaVector.y, deltaVector.x);
	else
		deltaAngle = atan2f(-deltaVector.y, -deltaVector.x) + PI;

	m_UnitState->FleeMotion(fleeFromPosition, deltaAngle);
}

void UnitBehavior::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	m_UnitState->Update(dt, mousePosition, units);
}

void UnitBehavior::Render(sf::RenderWindow *window)
{
	m_Unit->Render(window);
}

Unit* UnitBehavior::GetUnit()
{
	return m_Unit;
}

void UnitBehavior::SetUnit(Unit *unit)
{
	m_Unit = unit;
}


sf::Vector2f UnitBehavior::State::GetUnitPosition()
{
	return m_UnitBehavior->GetUnit()->GetPosition();
}

float UnitBehavior::State::GetUnitFacing()
{
	return m_UnitBehavior->GetUnit()->GetFacing();
}

float UnitBehavior::State::GetUnitFear()
{
	return m_UnitBehavior->GetUnit()->GetFear();
}

float UnitBehavior::State::GetUnitSpeed()
{
	return m_UnitBehavior->GetUnit()->GetSpeed();
}

void UnitBehavior::State::SetUnitPosition(sf::Vector2f position)
{
	m_UnitBehavior->GetUnit()->SetPosition(position);
}

void UnitBehavior::State::SetUnitFacing(float facing)
{
	m_UnitBehavior->GetUnit()->SetFacing(facing);
}

UnitBehavior::State::State(State *parentState, UnitBehavior *unitBehavior)
	: m_ParentState(parentState),
	m_UnitBehavior(unitBehavior)
{

}


void UnitBehavior::LeafState::Transit(State *from, State *to)
{
	m_ParentState->Transit(from, to);
}

void UnitBehavior::LeafState::Enter(bool initialization){}

void UnitBehavior::LeafState::Exit(bool finalization){}

bool UnitBehavior::LeafState::CreationPhase()
{
	return false;
}

bool UnitBehavior::LeafState::AlivePhase()
{
	return false;
}

bool UnitBehavior::LeafState::DestructionPhase()
{
	return false;
}

bool UnitBehavior::LeafState::DeadPhase()
{
	return false;
}

bool UnitBehavior::LeafState::StandIdleMotion()
{
	return false;
}

bool UnitBehavior::LeafState::TurnIdleMotion()
{
	return false;
}

bool UnitBehavior::LeafState::WalkIdleMotion()
{
	return false;
}

bool UnitBehavior::LeafState::ChaseMotion(UnitBehavior *target)
{
	return false;
}

bool UnitBehavior::LeafState::FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle)
{
	return false;
}

bool UnitBehavior::LeafState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	return false;
}

UnitBehavior::LeafState::LeafState(State *parentState, UnitBehavior *unitBehavior)
	: State(parentState, unitBehavior)
{

}


void UnitBehavior::DecoratedState::Transit(State *from, State *to)
{
	if (m_ChildState == from)
	{
		m_ChildState->Exit(false);
		delete m_ChildState;
		m_ChildState = to;
		m_ChildState->Enter(false);
	}
	else
	{
		m_ParentState->Transit(from, to);
	}
}

void UnitBehavior::DecoratedState::Enter(bool initialization)
{
	m_ChildState->Enter(initialization);
}

void UnitBehavior::DecoratedState::Exit(bool finalization)
{
	m_ChildState->Exit(finalization);
	delete m_ChildState;
}

bool UnitBehavior::DecoratedState::CreationPhase()
{
	return m_ChildState->CreationPhase();
}

bool UnitBehavior::DecoratedState::AlivePhase()
{
	return m_ChildState->AlivePhase();
}

bool UnitBehavior::DecoratedState::DestructionPhase()
{
	return m_ChildState->DestructionPhase();
}

bool UnitBehavior::DecoratedState::DeadPhase()
{
	return m_ChildState->DeadPhase();
}

bool UnitBehavior::DecoratedState::StandIdleMotion()
{
	return m_ChildState->StandIdleMotion();
}

bool UnitBehavior::DecoratedState::TurnIdleMotion()
{
	return m_ChildState->TurnIdleMotion();
}

bool UnitBehavior::DecoratedState::WalkIdleMotion()
{
	return m_ChildState->WalkIdleMotion();
}

bool UnitBehavior::DecoratedState::ChaseMotion(UnitBehavior *target)
{
	return m_ChildState->ChaseMotion(target);
}

bool UnitBehavior::DecoratedState::FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle)
{
	return m_ChildState->FleeMotion(fleeFromPosition, fleeFromAngle);
}

bool UnitBehavior::DecoratedState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	return m_ChildState->Update(dt, mousePosition, units);
}

UnitBehavior::DecoratedState::DecoratedState(State *parentState, UnitBehavior *unitBehavior)
	: State(parentState, unitBehavior)
{

}


void UnitBehavior::CompositeState::Transit(State *from, State *to)
{
	bool contains = false;
	for each (State *s in m_ChildStates)
	{
		if (from == s)
		{
			s->Exit(false);
			delete s;
			s = to;
			s->Enter(false);
			contains = true;
			break;
		}
	}
	if (!contains)
	{
		m_ParentState->Transit(from, to);
	}
}

void UnitBehavior::CompositeState::Enter(bool initialization)
{
	for each (State *s in m_ChildStates)
	{
		s->Enter(initialization);
	}
}

void UnitBehavior::CompositeState::Exit(bool finalization)
{
	for each (State *s in m_ChildStates)
	{
		s->Exit(finalization);
		delete s;
	}
	m_ChildStates.clear();
}

bool UnitBehavior::CompositeState::CreationPhase()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->CreationPhase())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::AlivePhase()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->AlivePhase())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::DestructionPhase()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->DestructionPhase())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::DeadPhase()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->DeadPhase())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::StandIdleMotion()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->StandIdleMotion())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::TurnIdleMotion()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->TurnIdleMotion())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::WalkIdleMotion()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->WalkIdleMotion())
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::ChaseMotion(UnitBehavior *target)
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->ChaseMotion(target))
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle)
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->FleeMotion(fleeFromPosition, fleeFromAngle))
			handled = true;
	}
	return handled;
}

bool UnitBehavior::CompositeState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->Update(dt, mousePosition, units))
			handled = true;
	}
	return handled;
}

UnitBehavior::CompositeState::CompositeState(State *parentState, UnitBehavior *unitBehavior)
	: State(parentState, unitBehavior)
{

}


UnitBehavior::PhaseState::PhaseState(State *parentState, UnitBehavior *unitBehavior)
	: DecoratedState(parentState, unitBehavior)
{
	CreationState *startPhaseState = new CreationState(this, unitBehavior);
	m_ChildState = startPhaseState;
}

bool UnitBehavior::PhaseState::CreationPhase()
{
	if (!m_ChildState->CreationPhase())
	{
		Transit(m_ChildState, new CreationState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::PhaseState::AlivePhase()
{
	if (!m_ChildState->AlivePhase())
	{
		Transit(m_ChildState, new AliveState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::PhaseState::DestructionPhase()
{
	if (!m_ChildState->DestructionPhase())
	{
		Transit(m_ChildState, new DestructionState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::PhaseState::DeadPhase()
{
	if (!m_ChildState->DeadPhase())
	{
		Transit(m_ChildState, new DeadState(this, m_UnitBehavior));
	}
	return true;
}


UnitBehavior::MotionState::MotionState(State *parentState, UnitBehavior *unitBehavior)
	: DecoratedState(parentState, unitBehavior)
{
	IdleState *startIdleState = new IdleState(this, unitBehavior);
	m_ChildState = startIdleState;
}

bool UnitBehavior::MotionState::StandIdleMotion()
{
	if (!m_ChildState->StandIdleMotion())
	{
		Transit(m_ChildState, new IdleState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::MotionState::TurnIdleMotion()
{
	if (!m_ChildState->TurnIdleMotion())
	{
		Transit(m_ChildState, new IdleState(this, m_UnitBehavior));
		m_ChildState->TurnIdleMotion();
	}
	return true;
}

bool UnitBehavior::MotionState::WalkIdleMotion()
{
	if (!m_ChildState->WalkIdleMotion())
	{
		Transit(m_ChildState, new IdleState(this, m_UnitBehavior));
		m_ChildState->TurnIdleMotion();
	}
	return true;
}

bool UnitBehavior::MotionState::ChaseMotion(UnitBehavior *target)
{
	if (!m_ChildState->ChaseMotion(target))
	{
		Transit(m_ChildState, new ChaseState(this, m_UnitBehavior));
		m_ChildState->ChaseMotion(target);
	}
	return true;
}

bool UnitBehavior::MotionState::FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle)
{
	if (!m_ChildState->FleeMotion(fleeFromPosition, fleeFromAngle))
	{
		Transit(m_ChildState, new FleeState(this, m_UnitBehavior));
		m_ChildState->FleeMotion(fleeFromPosition, fleeFromAngle);
	}
	return true;
}


UnitBehavior::UnitState::UnitState(State *parentState, UnitBehavior *unitBehavior)
	: CompositeState(parentState, unitBehavior)
{
	PhaseState *startPhaseState = new PhaseState(this, unitBehavior);
	MotionState *startMotionState = new MotionState(this, unitBehavior);
	m_ChildStates.push_back(startPhaseState);
	m_ChildStates.push_back(startMotionState);
}


UnitBehavior::CreationState::CreationState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::CreationState::CreationPhase()
{
	return true;
}


UnitBehavior::AliveState::AliveState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::AliveState::AlivePhase()
{
	return true;
}


UnitBehavior::DestructionState::DestructionState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::DestructionState::DestructionPhase()
{
	return true;
}


UnitBehavior::DeadState::DeadState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::DeadState::DeadPhase()
{
	return true;
}


UnitBehavior::IdleState::IdleState(State *parentState, UnitBehavior *unitBehavior)
	: DecoratedState(parentState, unitBehavior)
{
	StandIdleState *startIdleState = new StandIdleState(this, unitBehavior);
	m_ChildState = startIdleState;
	m_IdleTimer.restart();
	m_StateLength = 500 + (rand() % 500);
}

bool UnitBehavior::IdleState::StandIdleMotion()
{
	if (!m_ChildState->StandIdleMotion())
	{
		Transit(m_ChildState, new StandIdleState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::IdleState::TurnIdleMotion()
{
	if (!m_ChildState->TurnIdleMotion())
	{
		Transit(m_ChildState, new TurnIdleState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::IdleState::WalkIdleMotion()
{
	if (!m_ChildState->WalkIdleMotion())
	{
		Transit(m_ChildState, new WalkIdleState(this, m_UnitBehavior));
	}
	return true;
}

bool UnitBehavior::IdleState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	if (m_IdleTimer.getElapsedTime().asMilliseconds() > 3000 && m_UnitBehavior->GetUnit()->IsWolf())
	{
		float closest = 10000.f;
		UnitBehavior *closestTarget = units[0];
		for each (UnitBehavior *u in units)
		{
			sf::Vector2f v = u->GetUnit()->GetPosition() - GetUnitPosition();
			float distance = sqrtf((v.x * v.x) + (v.y * v.y));
			if (distance < closest)
				closestTarget = u;
		}
		m_UnitBehavior->ChaseMotion(closestTarget);
		return true;
	}
	else if (m_IdleTimer.getElapsedTime().asMilliseconds() > m_StateLength)
	{
		if (m_IdleTimer.getElapsedTime().asMilliseconds() > 3000)
		{
			m_StateLength -= 3000;
			m_IdleTimer.restart();
		}
		int randomNr = rand() % 3;
		if (randomNr < 1)
			StandIdleMotion();
		else if (randomNr < 2)
			TurnIdleMotion();
		else
			WalkIdleMotion();
		m_StateLength += 500 + (rand() % 1000);
	}
	return m_ChildState->Update(dt, mousePosition, units);
}


UnitBehavior::StandIdleState::StandIdleState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::StandIdleState::StandIdleMotion()
{
	return true;
}

bool UnitBehavior::StandIdleState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	return true;
}


UnitBehavior::TurnIdleState::TurnIdleState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{
	
}

bool UnitBehavior::TurnIdleState::TurnIdleMotion()
{
	m_TurnAngle = ((float)rand() / RAND_MAX) * 0.03f;
	m_TurnAngle -= 0.015f;
	return true;
}

bool UnitBehavior::TurnIdleState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	m_UnitBehavior->GetUnit()->OffsetFacing(m_TurnAngle);
	return true;
}


UnitBehavior::WalkIdleState::WalkIdleState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::WalkIdleState::WalkIdleMotion()
{
	m_Speed = ((float)rand() / RAND_MAX) * (GetUnitSpeed() - 0.2);
	m_Speed += 0.2;
	m_TurnAngle = ((float)rand() / RAND_MAX) * 0.01f;
	m_TurnAngle -= 0.005f;
	return true;
}

bool UnitBehavior::WalkIdleState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	m_UnitBehavior->GetUnit()->OffsetFacing(m_TurnAngle);
	m_UnitBehavior->GetUnit()->Move(m_Speed);
	return true;
}


UnitBehavior::ChaseState::ChaseState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{

}

bool UnitBehavior::ChaseState::ChaseMotion(UnitBehavior *target)
{
	m_Target = target;
	return true;
}

bool UnitBehavior::ChaseState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	float deltaAngle;
	sf::Vector2f deltaVector = m_Target->GetUnit()->GetPosition() - GetUnitPosition();
	if (GetUnitPosition().y >= 0)
		deltaAngle = atan2f(deltaVector.y, deltaVector.x);
	else
		deltaAngle = atan2f(-deltaVector.y, -deltaVector.x) + PI;
	float angleDifference = GetUnitFacing() - deltaAngle;
	if (angleDifference < 0)
		angleDifference += PI * 2;
	if (angleDifference > PI)
		m_UnitBehavior->GetUnit()->OffsetFacing(0.1f);
	else if (angleDifference < PI)
		m_UnitBehavior->GetUnit()->OffsetFacing(-0.1f);
	if (angleDifference <= PI / 2 || angleDifference >= (PI / 2) * 3)
		m_UnitBehavior->GetUnit()->Move();
	return true;
}


UnitBehavior::FleeState::FleeState(State *parentState, UnitBehavior *unitBehavior)
	: LeafState(parentState, unitBehavior)
{
	
}

bool UnitBehavior::FleeState::FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle)
{
	m_FleeFromPosition = fleeFromPosition;
	m_FleeFromAngle = fleeFromAngle;
	return true;
}

bool UnitBehavior::FleeState::Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units)
{
	sf::Vector2f deltaVector = m_FleeFromPosition - GetUnitPosition();
	float fleeAngle = m_FleeFromAngle + PI, distance = sqrtf((deltaVector.x * deltaVector.x) + (deltaVector.y * deltaVector.y));
	if (distance < GetUnitFear() * 1.5f)
	{
		float angleDifference = GetUnitFacing() - fleeAngle;
		if (angleDifference < 0) angleDifference += PI * 2;
		if (angleDifference > PI) m_UnitBehavior->GetUnit()->OffsetFacing(0.1f);
		else if (angleDifference < PI) m_UnitBehavior->GetUnit()->OffsetFacing(-0.1f);
		if (angleDifference <= PI / 2 || angleDifference >= (PI / 2) * 3) m_UnitBehavior->GetUnit()->Move();
	}
	else
	{
		m_UnitBehavior->IdleMotion();
	}
	return true;
}