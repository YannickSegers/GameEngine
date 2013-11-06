#ifndef __InputManager_H_
#define __InputManager_H_
#include <iostream>
#include "Util.h"
#include <vector>
#include <map>

typedef map<tstring,vector<int> >::value_type CommandPair;

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	void Update();
	bool IsKeyDown(int vKey) const;
	bool IsKeyUp(int vKey) const;
	bool IsKeyHeldDown(int vKey) const;

	void RegisterCommand(const tstring& commandName, const vector<int>* keys);
	void RemoveCommand(const tstring& commandName);
	bool IsCommandDown(const tstring& commandName) const;
	bool IsCommandUp(const tstring& commandName) const;
	bool IsCommandHeldDown(const tstring& commandName) const;

private:
	unsigned char m_CurrentKeyboardState[256];
	unsigned char m_PreviousKeyboardState[256];
	map<tstring,vector<int> > m_RegisteredCommands;
}
;
#endif