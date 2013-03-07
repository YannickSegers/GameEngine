#include "Engine.h"
#include "Device_WIN32.h"
//Initialize statics
Engine* Engine::s_pEngine = NULL;

Engine::Engine()
	:m_pDevice(0)
	,m_pGame(0)
{
#ifdef WIN32
	m_pDevice = new Device_WIN32(WINDOWWIDTH,WINDOWHEIGHT);
#endif
}

Engine::~Engine()
{
	delete m_pDevice;
	delete m_pGame;
}

Engine* Engine::GetSingleton()
{
	if ( s_pEngine == NULL) s_pEngine = new Engine();
	return s_pEngine;
}

bool Engine::Run()
{
	// create the game engine object, exit if failure
	if (Engine::GetSingleton() == NULL) return false;

	// If no game has been set, exit
	if(m_pGame == NULL) return false;

	//Initialize the Graphics
	if(!m_pDevice->InitDisplay()) return false;

	/*if(!InitBuffer()) return false; is the same as the onResize method of the finalproject

	if(!InitShader()) return false;

	if(!InitCamera()) return false;
	InitProjectionMatrix();*/

	m_pGame->InitializeElements();

#ifdef WIN32
	// Enter the main message loop
	MSG msg = {0};
	while ( WM_QUIT != msg.message )
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Process the message
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_pGame->Update();
			m_pGame->Render();
		}
	}

	CleanUpDevice();
	return msg.wParam?true:false;
#endif
}

void Engine::CleanUpDevice()
{
	m_pDevice->CleanUp();
	delete this;
}

void Engine::SetGame(AbstractGame* game)
{
	m_pGame = game;
}

Device* Engine::GetDevice()
{
	return m_pDevice;
}

#ifdef WIN32
bool Engine::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	assert(m_pDevice != NULL);
	Device_WIN32* pDevice_Win32 = dynamic_cast<Device_WIN32*>(m_pDevice);
	return pDevice_Win32->InitWindow(hInstance,nCmdShow);
}
#endif