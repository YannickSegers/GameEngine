#ifndef __Engine_H_
#define __Engine_H_

//Includes
#include "Util.h"
#include "AbstractGame.h"
#include "Device.h"
#include "ShaderManager.h"
class InputManager;

// Magic numbers
const int WINDOWWIDTH = 640;
const int WINDOWHEIGHT = 480;

/*
* Main Engine Class, which starts up the game
* Is a singleton, so only one can be created
*/
class Engine
{
private:
	// private constructor for the singleton implementations
	Engine();
	//static pointer for singleton
	static Engine* s_pEngine;

public:
	virtual ~Engine();

	//---------
	//Methods
	//---------
	static Engine* GetSingleton();

	bool Run();
	//bool InitDisplay();

#ifdef WIN32
	bool InitWindow(HINSTANCE hInstance, int nCmdShow);
#endif
	void CleanUpDevice();

	void SetGame(AbstractGame* game);
	bool InitShaders();
	Device* GetDevice();
	ShaderManager* GetShaderManager();
	InputManager* GetInputManager();

private:
	//-----------------
	//Member Methods
	//-----------------

	//-----------------
	//Member Variables
	//-----------------
	AbstractGame* m_pGame;
	Device* m_pDevice;
	ShaderManager* m_pShaderManager;
	InputManager* m_pInputManager;

};
#endif