#ifndef GAMESTATE_MANAGER_H
#define	GAMESTATE_MANAGER_H

#include <map>
#include <list>
#include <string>
class IGameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update(double dt);
	void Draw();

	void RegisterState(std::string _name, IGameState* _state);
	void Push(std::string _name);
	void Pop();
protected:
private:
	std::map<std::string, IGameState*> m_gameStates;
	std::list<IGameState*> m_stack;
};


class IGameState
{
public:

	virtual void Update(double dt) {};
	virtual void Draw() {};

	bool isUpdateBlocking() {return m_updateBlocking;}
	bool isDrawBlocking()	{return m_drawBlocking;}

	void SetUpdateBlocking(bool _block) {m_updateBlocking = _block;}
	void SetDrawBlocking(bool _block) { m_drawBlocking = _block;}

protected:
private:
	bool m_updateBlocking;
	bool m_drawBlocking;
};
#endif