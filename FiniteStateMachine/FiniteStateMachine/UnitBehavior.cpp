#include "UnitBehavior.h"

UnitBehavior::UnitBehavior()
{

}

UnitBehavior::~UnitBehavior()
{

}

void UnitBehavior::CreationPhase()
{

}

void UnitBehavior::AlivePhase()
{

}

void UnitBehavior::DestructionPhase()
{

}

void UnitBehavior::DeadPhase()
{

}

void UnitBehavior::Update()
{

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

bool UnitBehavior::LeafState::Update()
{
	return false;
}

void UnitBehavior::DecoratedState::Transit(State *from, State *to)
{
	if (m_ChildState == from)
	{
		m_ChildState->Exit(false);
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

bool UnitBehavior::DecoratedState::Update()
{
	return m_ChildState->Update();
}

void UnitBehavior::CompositeState::Transit(State *from, State *to)
{
	bool contains = false;
	for each (State *s in m_ChildStates)
	{
		if (from == s)
		{
			s->Exit(false);
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
	}
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

bool UnitBehavior::CompositeState::Update()
{
	bool handled = false;
	for each (State *s in m_ChildStates)
	{
		if (s->Update())
			handled = true;
	}
	return handled;
}