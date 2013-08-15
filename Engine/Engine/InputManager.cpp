#include "InputManager.h"
#include "Util.h"

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
