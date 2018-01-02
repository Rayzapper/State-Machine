#ifndef RAYZAPPER_UNITBEHAVIOR_H
#define RAYZAPPER_UNITBEHAVIOR_H

#include <vector>

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
	void Update();
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
		virtual bool Update() = 0;
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
		virtual bool Update();
	protected:
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
		virtual bool Update();
	protected:

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
		virtual bool Update();
	protected:
		vector<State*> m_ChildStates;
	};

	State *UnitState;
};

#endif