#include "Game.h"
#include "Engine.h"

#define ENGINE (Engine::GetSingleton())

Game::Game()
{

}

Game::~Game()
{

}

void Game::InitializeElements()
{

}

void Game::Update()
{

}

void Game::Render()
{
	float clearColor[4] =  { 0.0f, 0.125f, 0.6f, 1.0f };
	ENGINE->GetDevice()->ClearRenderTargetView(clearColor);
	ENGINE->GetDevice()->PresentSwapChain();
}
