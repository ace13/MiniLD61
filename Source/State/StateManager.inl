#include "StateManager.hpp"
#include <type_traits>

template<typename T>
void StateManager::changeState(bool remove)
{
	static_assert(std::is_base_of<IState, T>::value, "Can only change to states.");

	IState* to = getState<T>(), *from = mCurState;
	if (!to)
	{
		to = new T();
		addState(typeid(T), to);
		
		to->init();
	}

	changeState(to);

	if (remove && from)
		removeState(from);
}

template<typename T>
void StateManager::removeState()
{
	static_assert(std::is_base_of<IState, T>::value, "Can only remove states.");
	IState* toRemove = getState<T>();
	if (toRemove)
		removeState(toRemove);
}

template<typename T>
IState* StateManager::getState() const
{
	static_assert(std::is_base_of<IState, T>::value, "Can only get states.");
	if (mStates.count(typeid(T)) > 0)
		return mStates.at(typeid(T));
	return nullptr;
}

