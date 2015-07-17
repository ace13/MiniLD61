#pragma once

#include <typeindex>
#include <unordered_map>

namespace sf { struct Event; class RenderTarget; }

class StateManager;

class IState
{
public:
	virtual ~IState() { }

	virtual void init() {}
	virtual void cleanup() {}

	virtual void handle_event(sf::Event& ev) = 0;
	virtual void fixed_update(float dt) = 0;
	virtual void variadic_update(float dt) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;

	virtual std::string getName() const = 0;

protected:
	StateManager& getStateManager() const;

private:
	StateManager* mStateMan;
	friend class StateManager;
};

class StateManager
{
public:
	StateManager();
	~StateManager();

	template<typename T>
	void changeState(bool remove = false);
	template<typename T>
	void removeState();
	template<typename T>
	IState* getState() const;
	IState* getCurrentState() const;

	void handle_event(sf::Event& ev);
	void fixed_update(float dt);
	void variadic_update(float dt);
	void draw(sf::RenderTarget& target);

private:
	void addState(const std::type_index& id, IState* state);
	void changeState(IState* state);
	void removeState(IState* state);

	IState* mCurState;
	std::unordered_map<std::type_index, IState*> mStates;
};

#include "StateManager.inl"

