#include "Game.h"
#include "Engine.h"
#include "RenderData.h"
#include "Camera.h"
#include "Cube.h"
#include "InputManager.h"

#define ENGINE (Engine::GetSingleton())

Game::Game()
	:m_pCube(0)
	,m_pCamera(0)
{

}

Game::~Game()
{
	D3DD11_DELETE_AND_CLEAN(m_pCube);
	D3DD11_DELETE_AND_CLEAN(m_pCamera);
}

void Game::InitializeElements()
{
	m_pCube = new Cube();
	m_pCube->Initialize();

	m_pCamera = new Camera();
	m_pCamera->Initialize(CAMERAPOS,TARGETPOS,UPVECTOR);
}

void Game::Update()
{
	m_pCube->Update();
	XMVECTOR cameraPos = XMLoadFloat3(&m_pCamera->GetCameraPos());
	/*cameraPos += XMVectorSet(0.0001f,0.0f,0.0f,0.0f);
	XMFLOAT3 newCameraPos;
	XMStoreFloat3(&newCameraPos,cameraPos);*/
	//cameraPos * XMMatrixRotationY(XM_PIDIV2/9.0f);

	//Camera Rotation code
	/*XMFLOAT3 newCameraPos;
	cameraPos = XMVector3Rotate(cameraPos,XMQuaternionRotationMatrix(XMMatrixRotationY(-(XM_PIDIV2/9000.0f))));
	XMStoreFloat3(&newCameraPos,cameraPos);
	m_pCamera->SetCameraPos(newCameraPos);
	m_pCamera->UpdateViewMatrix();*/

	//keyboard input test code
	//bool pressed = ENGINE->GetInputManager()->IsKeyDown(VK_UP);

	//cout << pressed;
	XMFLOAT3 newCameraPos;
	if(ENGINE->GetInputManager()->IsKeyDown(VK_UP))
	{
		cameraPos = XMVector3Rotate(cameraPos,XMQuaternionRotationMatrix(XMMatrixRotationX((XM_PIDIV2/9000.0f))));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(VK_DOWN))
	{
		cameraPos = XMVector3Rotate(cameraPos,XMQuaternionRotationMatrix(XMMatrixRotationX(-(XM_PIDIV2/9000.0f))));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(VK_LEFT))
	{
		cameraPos = XMVector3Rotate(cameraPos,XMQuaternionRotationMatrix(XMMatrixRotationY((XM_PIDIV2/9000.0f))));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(VK_RIGHT))
	{
		cameraPos = XMVector3Rotate(cameraPos,XMQuaternionRotationMatrix(XMMatrixRotationY(-(XM_PIDIV2/9000.0f))));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(0x57))//W
	{
		cameraPos = XMVector3Transform(cameraPos,XMMatrixTranslation(0,0,0.01f));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(0x53))//S
	{
		cameraPos = XMVector3Transform(cameraPos,XMMatrixTranslation(0,0,-0.01f));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(0x41))//A
	{
		cameraPos = XMVector3Transform(cameraPos,XMMatrixTranslation(-0.01f,0,0));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(0x44))//D
	{
		cameraPos = XMVector3Transform(cameraPos,XMMatrixTranslation(0.01f,0,0));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(0x51))//Q
	{
		cameraPos = XMVector3Transform(cameraPos,XMMatrixTranslation(0,-0.01f,0));
	}
	if(ENGINE->GetInputManager()->IsKeyDown(0x45))//E
	{
		cameraPos = XMVector3Transform(cameraPos,XMMatrixTranslation(0,0.01f,0));
	}
	
	XMStoreFloat3(&newCameraPos,cameraPos);
	m_pCamera->SetCameraPos(newCameraPos);
	m_pCamera->UpdateViewMatrix();
}

void Game::Render()
{
	//float clearColor[4] =  { 0.0f, 0.125f, 0.6f, 1.0f };
	float clearColor[4] =  { 0.0f, 0.0f, 0.0f, 1.0f };
	ENGINE->GetDevice()->ClearRenderTargetView(clearColor);
	ENGINE->GetDevice()->ClearDepthStencilView();
	ENGINE->GetDevice()->SetDepthStencilState();
	//Render The Meshes here
	RenderData renderdata;
	renderdata.SetCamera(m_pCamera);
	m_pCube->Render(&renderdata);
	ENGINE->GetDevice()->PresentSwapChain();
}
