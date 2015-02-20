#include "GameStateManager.h"

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::Update(double dt)
{

	for(auto* i = m_stack.front(); i < m_stack.back() + 1; i++)
	{
		i->Update(dt);
		if(i->isUpdateBlocking())
			return;
	}
}

void GameStateManager::Draw()
{
	for(auto* i = m_stack.front(); i < m_stack.back() + 1; i++)
	{
		i->Draw();
		if(i->isDrawBlocking())
			return;
	}
}

void GameStateManager::RegisterState(std::string _name, IGameState* _state)
{
	m_gameStates.insert(std::pair<std::string, IGameState*>(_name, _state));
}

void GameStateManager::Push(std::string _name)
{
	for(auto i = m_gameStates.begin(); i != m_gameStates.end(); i++)
	{
		if(i->first ==  _name) 
			m_stack.push_back(i->second);
	}
}

void GameStateManager::Pop()
{
	m_stack.pop_back();
}

