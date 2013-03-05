#include "Device_WIN32.h"


Device_WIN32::Device_WIN32(int width, int height)
	:Device(width,height)
{

}

Device_WIN32::~Device_WIN32()
{

}

bool Device_WIN32::InitDisplay()
{
	return true;
}

ID3D11Device* Device_WIN32::GetD3DDevice()
{
	return 0;
}

ID3D11DeviceContext* Device_WIN32::GetImmediateContext()
{
	return 0;
}

ID3D11VertexShader* Device_WIN32::GetVertexShader()
{
	return 0;
}

ID3D11PixelShader* Device_WIN32::GetPixelShader()
{
	return 0;
}

bool Device_WIN32::InitWindow(HINSTANCE hInstance, int nCmdShow)
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
	//RECT rc = { 0, 0, WINDOWWIDTH, WINDOWHEIGHT };
	RECT rc = { 0, 0, m_Width, m_Height};
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	m_hMainWnd = CreateWindow(L"Engine", L"Night Engine", WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
							NULL );
	if( !m_hMainWnd )
		return false;

	ShowWindow( m_hMainWnd, nCmdShow );

	return true;
}

LRESULT CALLBACK Device_WIN32::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
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