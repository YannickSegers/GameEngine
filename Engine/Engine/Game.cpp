#include "Game.h"
#include "Engine.h"

#define ENGINE (Engine::GetSingleton())

Game::Game()
	:m_pCube(0)
{

}

Game::~Game()
{
	D3DD11_DELETE_AND_CLEAN(m_pCube);
}

void Game::InitializeElements()
{
	m_pCube = new Cube();
	m_pCube->Initialize();
}

void Game::Update()
{
	m_pCube->Update();
}

void Game::Render()
{
	float clearColor[4] =  { 0.0f, 0.125f, 0.6f, 1.0f };
	ENGINE->GetDevice()->ClearRenderTargetView(clearColor);
	ENGINE->GetDevice()->ClearDepthStencilView();
	ENGINE->GetDevice()->SetDepthStencilState();
	//Render The Cube here
	m_pCube->Render();
	ENGINE->GetDevice()->PresentSwapChain();
}
