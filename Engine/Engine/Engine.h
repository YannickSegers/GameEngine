#ifndef __Engine_H_
#define __Engine_H_

//Includes
#include "Util.h"
#include "AbstractGame.h"

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
	bool InitDisplay();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool InitWindow(HINSTANCE hInstance, int nCmdShow);
	void CleanUpDevice();

	void SetGame(AbstractGame* game);

	ID3D11Device* GetD3DDevice();
	ID3D11DeviceContext* GetImmediateContext();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
private:
	//-----------------
	//Member Methods
	//-----------------
	//void Update();
	//void Render();
	void InitElements();

	//-----------------
	//Member Variables
	//-----------------
	HWND m_hMainWnd;

	AbstractGame* m_pGame;

};
#endif