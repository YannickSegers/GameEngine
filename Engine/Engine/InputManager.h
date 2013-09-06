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
	bool IsKeyDown(int vKey);
	bool IsKeyUp(int vKey);
	bool IsKeyHeldDown(int vKey);

	void RegisterCommand(const tstring& commandName, const vector<int>* keys);
	void RemoveCommand(const tstring& commandName);
	bool IsCommandDown(const tstring& commandName);
	bool IsCommandUp(const tstring& commandName);
	bool IsCommandHeldDown(const tstring& commandName);

private:
	unsigned char m_CurrentKeyboardState[256];
	unsigned char m_PreviousKeyboardState[256];
	map<tstring,vector<int> > m_RegisteredCommands;
}
;
#endif