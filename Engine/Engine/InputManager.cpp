#include "InputManager.h"
#include "Util.h"
#include <boost/foreach.hpp>

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::Update()
{
	memcpy(m_PreviousKeyboardState, m_CurrentKeyboardState, sizeof(m_CurrentKeyboardState)); 
	GetKeyboardState(m_CurrentKeyboardState);
}

bool InputManager::IsKeyDown(int vKey)
{
	unsigned char highBit = m_CurrentKeyboardState[vKey] & 0x80;
	if(highBit) return true;
 	return false;
}

bool InputManager::IsKeyUp(int vKey)
{
	unsigned char highBit = m_CurrentKeyboardState[vKey] & 0x80;
	if(!highBit) return true;
	return false;
}

bool InputManager::IsKeyHeldDown(int vKey)
{
	if( (m_PreviousKeyboardState[vKey] & 0x80) && (m_CurrentKeyboardState[vKey] & 0x80)) return true;
	return false;
}

void InputManager::RegisterCommand(const tstring& commandName, const vector<int>* keys)
{
	if(m_RegisteredCommands.find(commandName) == m_RegisteredCommands.end())
	{
		m_RegisteredCommands.insert(std::make_pair(commandName,*keys));
	}
}

void InputManager::RemoveCommand(const tstring& commandName)
{
	if(m_RegisteredCommands.find(commandName) != m_RegisteredCommands.end())
	{
		m_RegisteredCommands.erase(commandName);
	}
}

bool InputManager::IsCommandDown(const tstring& commandName)
{
	map<tstring,vector<int> >::iterator pos = m_RegisteredCommands.find(commandName);
	if(pos != m_RegisteredCommands.end())
	{
		BOOST_FOREACH(int commandKey, pos->second)
		{
			if(IsKeyDown(commandKey))
			{
				return true;
			}
		}
	}
	return false;
}

bool InputManager::IsCommandUp(const tstring& commandName)
{
	map<tstring,vector<int> >::iterator pos = m_RegisteredCommands.find(commandName);
	if(pos != m_RegisteredCommands.end())
	{
		BOOST_FOREACH(int commandKey, pos->second)
		{
			if(IsKeyUp(commandKey))
			{
				return true;
			}
		}
	}
	return false;
}

bool InputManager::IsCommandHeldDown(const tstring& commandName)
{
	map<tstring,vector<int> >::iterator pos = m_RegisteredCommands.find(commandName);
	if(pos != m_RegisteredCommands.end())
	{
		BOOST_FOREACH(int commandKey, pos->second)
		{
			if(IsKeyHeldDown(commandKey))
			{
				return true;
			}
		}
	}
	return false;
}

