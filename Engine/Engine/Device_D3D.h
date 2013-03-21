#ifndef __Device_D3D_H_
#define __Device_D3D_H_

//Includes
#include "Device.h"
//#include "Util.h"

//The Win32 device which will create the window and manage the DirectX components
class Device_D3D: public Device
{
public:
	Device_D3D(int width, int height);
	virtual ~Device_D3D();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool InitWindow(HINSTANCE hInstance, int nCmdShow);

	virtual bool InitDisplay();
	virtual bool ResizeBuffers();
	virtual void CleanUp();

	virtual Pi3DDevice* Get3DDevice();
	ID3D11DeviceContext* GetImmediateContext();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();

	virtual void ClearRenderTargetView(const float* clearColor);
	virtual void PresentSwapChain();
private:
	HWND m_hMainWnd;

	ID3D11Device* m_pD3DDevice;
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	ID3D11DeviceContext* m_pImmediateContext;
	IDXGISwapChain*  m_pSwapChain;

	ID3D11Texture2D* m_pDepthStencilBuffer;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11DepthStencilView* m_pDepthStencilView;

	//ID3D11RasterizerState* m_pRasterizerState;

	ID3D11Buffer* m_pCBNeverChanges;
	ID3D11Buffer* m_pCBChangeOnResize;

	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pVertexLayout;

	int m_CurrentBackBufferWidth;
	int m_CurrentBackBufferHeight;
};
#endif