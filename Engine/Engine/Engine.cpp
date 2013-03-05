#include "Engine.h"

//Initialize statics
Engine* Engine::s_pEngine = NULL;

Engine::Engine()
	:m_pGame(0)
{
}

Engine::~Engine()
{
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

	//Initialize DirectX
	if(!InitDisplay()) return false;

	/*if(!InitBuffer()) return false;

	if(!InitShader()) return false;

	if(!InitCamera()) return false;
	InitProjectionMatrix();*/

	m_pGame->InitializeElements();

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
}

bool Engine::InitDisplay()
{
	return true;
}


void Engine::CleanUpDevice()
{
	delete this;
}

void Engine::SetGame(AbstractGame* game)
{
	m_pGame = game;
}

//void Engine::Update()
//{
//
//}
//
//void Engine::Render()
//{
//
//}

void Engine::InitElements()
{

}

ID3D11Device* Engine::GetD3DDevice()
{
	return 0;
}

ID3D11DeviceContext* Engine::GetImmediateContext()
{
	return 0;
}

ID3D11VertexShader* Engine::GetVertexShader()
{
	return 0;
}

ID3D11PixelShader* Engine::GetPixelShader()
{
	return 0;
}

bool Engine::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	 // Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Engine";
	wcex.hIconSm = NULL;
	if( !RegisterClassEx( &wcex ) )
		return false;

	// Create window 
	RECT rc = { 0, 0, WINDOWWIDTH, WINDOWHEIGHT };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	m_hMainWnd = CreateWindow(L"Engine", L"Night Engine", WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
							NULL );
	if( !m_hMainWnd )
		return false;

	ShowWindow( m_hMainWnd, nCmdShow );

	return true;
}

LRESULT CALLBACK Engine::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch( message )
		{
			case WM_PAINT:
				hdc = BeginPaint( hWnd, &ps );
				EndPaint( hWnd, &ps );
				break;

			case WM_DESTROY:
				PostQuitMessage( 0 );
				break;

			default:
				return DefWindowProc( hWnd, message, wParam, lParam );
		}

		return 0;
	}