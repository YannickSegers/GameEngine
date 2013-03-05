#ifndef __Device_WIN32_H_
#define __Device_WIN32_H_

//Includes
#include "Device.h"
#include "Util.h"

//The Win32 device which will create the window and manage the DirectX components
class Device_WIN32: public Device
{
public:
	Device_WIN32(int width, int height);
	virtual ~Device_WIN32();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool InitWindow(HINSTANCE hInstance, int nCmdShow);

	virtual bool InitDisplay();

	ID3D11Device* GetD3DDevice();
	ID3D11DeviceContext* GetImmediateContext();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
private:
	HWND m_hMainWnd;
};
#endif