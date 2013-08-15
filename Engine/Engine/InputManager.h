#ifndef __InputManager_H_
#define __InputManager_H_
#include <iostream>
class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	void Update();
	bool IsKeyDown(int vKey);
	bool IsKeyUp(int vKey);
	bool IsKeyHeldDown(int vKey);
private:
	unsigned char m_CurrentKeyboardState[256];
	unsigned char m_PreviousKeyboardState[256];
}
;
#endif