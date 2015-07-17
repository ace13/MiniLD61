#include "StateManager.hpp"
#include <iostream>

StateManager& IState::getStateManager() const
{
	return *mStateMan;
}

StateManager::StateManager() :
	mCurState(nullptr)
{
}

StateManager::~StateManager()
{
	for (auto& st : mStates)
	{
		delete st.second;
	}
}

IState* StateManager::getCurrentState() const
{
	return mCurState;
}

void StateManager::handle_event(sf::Event& ev)
{
	if (mCurState)
		mCurState->handle_event(ev);
}
void StateManager::fixed_update(float dt)
{
	if (mCurState)
		mCurState->fixed_update(dt);
}
void StateManager::variadic_update(float dt)
{
	if (mCurState)
		mCurState->variadic_update(dt);
}
void StateManager::draw(sf::RenderTarget& target)
{
	if (mCurState)
		mCurState->draw(target);
}

void StateManager::addState(const std::type_index& id, IState* state)
{
	if (mStates.count(id) > 0)
	{
		removeState(mStates[id]);
	}

	mStates[id] = state;
	state->mStateMan = this;
}
void StateManager::changeState(IState* state)
{
	std::cout << "[SM] State changed to " << state->getName() << std::endl;
	mCurState = state;	
}
void StateManager::removeState(IState* state)
{
	state->cleanup();

	for (auto& it : mStates)
		if (it.second == state)
		{
			mStates.erase(it.first);
			delete state;
			return;
		}

	// Didn't exist in the state map, delete anyway
	delete state;
}
