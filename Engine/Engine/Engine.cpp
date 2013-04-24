#include "Engine.h"
#include "Device_D3D.h"
//Initialize statics
Engine* Engine::s_pEngine = NULL;

Engine::Engine()
	:m_pDevice(0)
	,m_pGame(0)
	,m_pShaderManager(0)
{
#ifdef WIN32
	m_pDevice = new Device_D3D(WINDOWWIDTH,WINDOWHEIGHT);
#endif
	m_pShaderManager = new ShaderManager();
}

Engine::~Engine()
{
	delete m_pShaderManager;
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

	//if(!InitBuffer()) return false; is the same as the onResize method of the finalproject

	if(!InitShaders()) return false;

	/*if(!InitCamera()) return false;
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

bool  Engine::InitShaders()
{
	HRESULT hr = S_OK;
	// Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;
	//hr = m_pShaderManager->CompileShaderFromFile( L"shaders.fx", "VS", "vs_4_0", &pVSBlob );
	hr = m_pShaderManager->CompileShaderFromFile( L"Shaders/BasicShader.fx", "VS", "vs_4_0", &pVSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return false;
    }

    // Create the vertex shader
	ID3D11VertexShader* vertexShader;
	hr = m_pDevice->Get3DDevice()->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &vertexShader );
	D3DD11_SET_DEGUG_NAME(vertexShader,"m_pVertexShader");
    if( FAILED( hr ) )
    {    
        pVSBlob->Release();
        return false;
    }
	m_pShaderManager->AddVertexShader(_T("VertexShader"),vertexShader);
	ID3D11InputLayout* inputLayout = 0;
#if 1
	if(!m_pShaderManager->GenerateInputLayoutFromVertexShader(pVSBlob,&inputLayout))
	{
		return false;
	}
#else
	// Old input layout code
    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE( layout );

    // Create the input layout
    hr =  m_pDevice->Get3DDevice()->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                          pVSBlob->GetBufferSize(), &inputLayout );
#endif
	D3DD11_SET_DEGUG_NAME(inputLayout,"m_pVertexLayout");
    pVSBlob->Release();
    if( FAILED( hr ) )
        return false;

	m_pShaderManager->AddInputLayout(_T("InputLayout"),inputLayout);

    // Compile the pixel shader
    ID3DBlob* pPSBlob = NULL;
    //hr = m_pShaderManager->CompileShaderFromFile( L"shaders.fx", "PS", "ps_4_0", &pPSBlob );
	hr = m_pShaderManager->CompileShaderFromFile( L"Shaders/BasicShader.fx", "PS", "ps_4_0", &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return false;
    }

    // Create the pixel shader
	ID3D11PixelShader* pixelShader;
    hr = m_pDevice->Get3DDevice()->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pixelShader );
	D3DD11_SET_DEGUG_NAME(pixelShader,"m_pPixelShader");
    pPSBlob->Release();
    if( FAILED( hr ) )
        return false;
	m_pShaderManager->AddPixelShader(_T("PixelShader"),pixelShader);
	return true;
}

void Engine::SetGame(AbstractGame* game)
{
	m_pGame = game;
}

Device* Engine::GetDevice()
{
	return m_pDevice;
}

ShaderManager* Engine::GetShaderManager()
{
	return m_pShaderManager;
}

#ifdef WIN32
bool Engine::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	assert(m_pDevice != NULL);
	Device_D3D* pDevice_D3D = dynamic_cast<Device_D3D*>(m_pDevice);
	return pDevice_D3D->InitWindow(hInstance,nCmdShow);
}
#endif