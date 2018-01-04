#ifndef RAYZAPPER_UNITBEHAVIOR_H
#define RAYZAPPER_UNITBEHAVIOR_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Unit.h"

using namespace std;

class UnitBehavior
{
public:
	UnitBehavior();
	~UnitBehavior();
	void CreationPhase();
	void AlivePhase();
	void DestructionPhase();
	void DeadPhase();
	void IdleMotion();
	void ChaseMotion(UnitBehavior *target);
	void FleeMotion(sf::Vector2f fleeFromPosition);
	void Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	void Render(sf::RenderWindow *window);
	Unit* GetUnit();
	void SetUnit(Unit *unit);
private:
	class State
	{
	public:
		virtual void Transit(State *to, State *from) = 0;
		virtual void Enter(bool initialization) = 0;
		virtual void Exit(bool finalization) = 0;
		virtual bool CreationPhase() = 0;
		virtual bool AlivePhase() = 0;
		virtual bool DestructionPhase() = 0;
		virtual bool DeadPhase() = 0;
		virtual bool StandIdleMotion() = 0;
		virtual bool TurnIdleMotion() = 0;
		virtual bool WalkIdleMotion() = 0;
		virtual bool ChaseMotion(UnitBehavior *target) = 0;
		virtual bool FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle) = 0;
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units) = 0;

		sf::Vector2f GetUnitPosition();
		float GetUnitFacing();
		float GetUnitFear();
		float GetUnitSpeed();
		void SetUnitPosition(sf::Vector2f position);
		void SetUnitFacing(float facing);
	protected:
		State *m_ParentState;
		UnitBehavior *m_UnitBehavior;
		State(State *parentState, UnitBehavior *unitBehavior);
	};

	class DecoratedState : public State
	{
	public:
		virtual void Transit(State *from, State *to);
		virtual void Enter(bool initialization);
		virtual void Exit(bool finalization);
		virtual bool CreationPhase();
		virtual bool AlivePhase();
		virtual bool DestructionPhase();
		virtual bool DeadPhase();
		virtual bool StandIdleMotion();
		virtual bool TurnIdleMotion();
		virtual bool WalkIdleMotion();
		virtual bool ChaseMotion(UnitBehavior *target);
		virtual bool FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle);
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	protected:
		DecoratedState(State *parentState, UnitBehavior *unitBehavior);
		State *m_ChildState;
	};

	class LeafState : public State
	{
	public:
		virtual void Transit(State *from, State *to);
		virtual void Enter(bool initialization);
		virtual void Exit(bool finalization);
		virtual bool CreationPhase();
		virtual bool AlivePhase();
		virtual bool DestructionPhase();
		virtual bool DeadPhase();
		virtual bool StandIdleMotion();
		virtual bool TurnIdleMotion();
		virtual bool WalkIdleMotion();
		virtual bool ChaseMotion(UnitBehavior *target);
		virtual bool FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle);
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	protected:
		LeafState(State *parentState, UnitBehavior *unitBehavior);
	};

	class CompositeState : public State
	{
	public:
		virtual void Transit(State *from, State *to);
		virtual void Enter(bool initialization);
		virtual void Exit(bool finalization);
		virtual bool CreationPhase();
		virtual bool AlivePhase();
		virtual bool DestructionPhase();
		virtual bool DeadPhase();
		virtual bool StandIdleMotion();
		virtual bool TurnIdleMotion();
		virtual bool WalkIdleMotion();
		virtual bool ChaseMotion(UnitBehavior *target);
		virtual bool FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle);
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	protected:
		CompositeState(State *parentState, UnitBehavior *unitBehavior);
		vector<State*> m_ChildStates;
	};

	class PhaseState : public DecoratedState
	{
	public:
		PhaseState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool CreationPhase();
		virtual bool AlivePhase();
		virtual bool DestructionPhase();
		virtual bool DeadPhase();
	private:

	};

	class MotionState : public DecoratedState
	{
	public:
		MotionState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool StandIdleMotion();
		virtual bool TurnIdleMotion();
		virtual bool WalkIdleMotion();
		virtual bool ChaseMotion(UnitBehavior *target);
		virtual bool FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle);
	private:

	};

	class UnitState : public CompositeState
	{
	public:
		UnitState(State *parentState, UnitBehavior *unitBehavior);
	private:

	};

	class CreationState : public LeafState
	{
	public:
		CreationState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool CreationPhase();
	private:

	};

	class AliveState : public LeafState
	{
	public:
		AliveState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool AlivePhase();
	private:

	};

	class DestructionState : public LeafState
	{
	public:
		DestructionState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool DestructionPhase();
	private:

	};

	class DeadState : public LeafState
	{
	public:
		DeadState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool DeadPhase();
	private:

	};

	class IdleState : public DecoratedState
	{
	public:
		IdleState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool StandIdleMotion();
		virtual bool TurnIdleMotion();
		virtual bool WalkIdleMotion();
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	private:
		sf::Clock m_IdleTimer;
		int m_StateLength;
	};

	class StandIdleState : public LeafState
	{
	public:
		StandIdleState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool StandIdleMotion();
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	};

	class TurnIdleState : public LeafState
	{
	public:
		TurnIdleState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool TurnIdleMotion();
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	private:
		float m_TurnAngle;
	};

	class WalkIdleState : public LeafState
	{
	public:
		WalkIdleState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool WalkIdleMotion();
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	private:
		float m_Speed, m_TurnAngle;
	};

	class ChaseState : public LeafState
	{
	public:
		ChaseState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool ChaseMotion(UnitBehavior *target);
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	private:
		UnitBehavior *m_Target;
	};

	class FleeState : public LeafState
	{
	public:
		FleeState(State *parentState, UnitBehavior *unitBehavior);
		virtual bool FleeMotion(sf::Vector2f fleeFromPosition, float fleeFromAngle);
		virtual bool Update(float dt, sf::Vector2i mousePosition, vector<UnitBehavior*> units);
	private:
		sf::Vector2f m_FleeFromPosition;
		float m_FleeFromAngle;
	};

	UnitState *m_UnitState;
	Unit *m_Unit;
};

#endif