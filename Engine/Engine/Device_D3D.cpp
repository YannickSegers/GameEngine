#include "Device_D3D.h"


Device_D3D::Device_D3D(int width, int height)
	:Device(width,height)
	,m_CurrentBackBufferWidth(0)
	,m_CurrentBackBufferHeight(0)
{

}

Device_D3D::~Device_D3D()
{
	//CleanUp();
}

//Initializes the Device, Swapchain and immediateContext
bool Device_D3D::InitDisplay()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect( m_hMainWnd, &rc );
	m_Width = rc.right - rc.left;
	m_Height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Multiple driver types so we can later select the one that works
	// the list is prioritized, so it checks the most important one first
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = m_Width;
    sd.BufferDesc.Height = m_Height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = REFRESHRATE;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hMainWnd;
    sd.SampleDesc.Count = 1; //Used for anti-aliasing
    sd.SampleDesc.Quality = 0; //Used for anti-aliasing
    sd.Windowed = TRUE;

	//Create the device and swapchain on the drivertype that works
    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        m_DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain( NULL, m_DriverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pD3DDevice, &m_FeatureLevel, &m_pImmediateContext );
		// Put here for debugging reasons
		D3DD11_SET_DEGUG_NAME(m_pSwapChain,"m_pSwapChain");
		D3DD11_SET_DEGUG_NAME(m_pD3DDevice,"m_pD3DDevice");
		D3DD11_SET_DEGUG_NAME(m_pImmediateContext,"m_pImmediateContext");

        if( SUCCEEDED( hr ) )
            break;
    }

	//Rest of the initialization is the same as the resize code
	hr = ResizeBuffers();

	// if anything failed, it will return false, otherwise true
	return SUCCEEDED(hr);
}

// Initializes the RenderTargetView and the Depth/Stencil buffer and view
// Also binds the RenderTargetView and Depth/Stencil view to the pipeline
// This method should also be called when the size of the window changes, as these views
// need to adapt to the new resolution
bool Device_D3D::ResizeBuffers()
{
	HRESULT hr = S_OK;

	//Only perform this code when the size has changed
	if((m_CurrentBackBufferWidth != m_Width) || (m_CurrentBackBufferHeight != m_Height))
	{
		//////////////////////////////
		//Creating the RenderTargetView
		//////////////////////////////

		//Retrieve the backbuffer
		ID3D11Texture2D* pBackBuffer = NULL;
		hr = m_pSwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		D3DD11_SET_DEGUG_NAME(pBackBuffer,"pBackBuffer");
		if(FAILED(hr)) return false;
	

		//Create the RenderTargetView
		hr = m_pD3DDevice->CreateRenderTargetView( pBackBuffer, 0, &m_pRenderTargetView);
		D3DD11_SET_DEGUG_NAME(m_pRenderTargetView,"m_pRenderTargetView");
		pBackBuffer->Release();
		if(FAILED(hr)) return false;

		//////////////////////////////
		//Creating the Depth/Stencil buffer and view
		//////////////////////////////

		//Create the DepthStencilBuffer
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = m_Width;
		depthStencilDesc.Height = m_Height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		hr = m_pD3DDevice->CreateTexture2D(&depthStencilDesc,0, &m_pDepthStencilBuffer);
		D3DD11_SET_DEGUG_NAME(m_pDepthStencilBuffer,"m_pDepthStencilBuffer");
		if(FAILED(hr)) return false;

		//Create the DepthStencilView
		hr = m_pD3DDevice->CreateDepthStencilView(m_pDepthStencilBuffer,0,&m_pDepthStencilView);
		D3DD11_SET_DEGUG_NAME(m_pDepthStencilView,"m_pDepthStencilView");
		if(FAILED(hr)) return false;

		// Bind the render target view and depth/stencil view to the pipeline.
		m_pImmediateContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView);

		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width    = (float)m_Width;
		vp.Height   = (float)m_Height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;

		m_pImmediateContext->RSSetViewports(1, &vp);
		//m_pImmediateContext->RSSetState(0); // Would it be better to fill in a rasterizerState?

		// Setup the raster description which will determine how and what polygons will be drawn.
		D3D11_RASTERIZER_DESC rasterDesc;
		rasterDesc.AntialiasedLineEnable = false;
		//rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_WIREFRAME; //D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		// Create the rasterizer state from the description we just filled out.
		hr = m_pD3DDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizerState);
		D3DD11_SET_DEGUG_NAME(m_pRasterizerState,"m_pRasterizerState");
		if(FAILED(hr))
		{
			return false;
		}

		// Now set the rasterizer state.
		m_pImmediateContext->RSSetState(m_pRasterizerState);
	}
	return SUCCEEDED(hr);
}

void Device_D3D::CleanUp()
{
	m_pSwapChain->SetFullscreenState(FALSE, NULL);
	/*D3DD11_RELEASE_AND_CLEAN(m_pVertexLayout);
	D3DD11_RELEASE_AND_CLEAN(m_pPixelShader);
	D3DD11_RELEASE_AND_CLEAN(m_pVertexShader);
	D3DD11_RELEASE_AND_CLEAN(m_pCBNeverChanges);
	D3DD11_RELEASE_AND_CLEAN(m_pCBChangeOnResize);*/
	D3DD11_RELEASE_AND_CLEAN(m_pDepthStencilBuffer);
	D3DD11_RELEASE_AND_CLEAN(m_pDepthStencilView);
	D3DD11_RELEASE_AND_CLEAN(m_pRenderTargetView);
	D3DD11_RELEASE_AND_CLEAN(m_pRasterizerState);
	D3DD11_RELEASE_AND_CLEAN(m_pSwapChain);
	D3DD11_RELEASE_AND_CLEAN(m_pImmediateContext);
	D3DD11_RELEASE_AND_CLEAN(m_pD3DDevice);
}

Pi3DDevice* Device_D3D::Get3DDevice()
{
	return m_pD3DDevice;
}

ID3D11DeviceContext* Device_D3D::GetImmediateContext()
{
	return m_pImmediateContext;
}

ID3D11VertexShader* Device_D3D::GetVertexShader()
{
	return m_pVertexShader;
}

ID3D11PixelShader* Device_D3D::GetPixelShader()
{
	return m_pPixelShader;
}

void Device_D3D::ClearRenderTargetView(const float* clearColor)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView,clearColor);
}

void Device_D3D::ClearDepthStencilView()
{
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0);
}

void Device_D3D::SetDepthStencilState()
{
	m_pImmediateContext->OMSetDepthStencilState(0, 0);
}

void Device_D3D::PresentSwapChain()
{
	m_pSwapChain->Present(0,0);
}

//Creates the window on a Windows system
bool Device_D3D::InitWindow(HINSTANCE hInstance, int nCmdShow)
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

LRESULT CALLBACK Device_D3D::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
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