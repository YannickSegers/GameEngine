#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Engine.h"
#include "Game.h"

#define ENGINE (Engine::GetSingleton())

#ifdef WIN32
using namespace std;
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
               LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	//notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL,0);

	// Enable run-time memory leak check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	if (ENGINE == NULL) return FALSE; // create the game engine and exit if it fails
	ENGINE->SetGame(new Game()); //Set the game it should play
	if(ENGINE->InitWindow(hInstance, nCmdShow))
	{
		return ENGINE->Run(); // run the game engine and return the result
	} else {
		return 0;
	}
}
#endif