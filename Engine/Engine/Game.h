#ifndef __Game_H_
#define __Game_H_

//Includes
#include "AbstractGame.h"
#include "Vertex.h"
#include <iostream>
class Cube;
class Camera;

const XMFLOAT3 CAMERAPOS = XMFLOAT3( 0.0f, 2.f, -5.0f );
const XMFLOAT3 TARGETPOS  = XMFLOAT3( 0.0f, 0.0f, 0.0f);
const XMFLOAT3 UPVECTOR  = XMFLOAT3( 0.0f, 1.0f, 0.0f);
//Game Class 
//Represents the actual game logic main class
class Game: public AbstractGame
{
public:
	Game();
	virtual ~Game();

	virtual void InitializeElements();
	virtual void Update();
	virtual void Render();
private:
	Cube* m_pCube;
	Camera* m_pCamera;
};
#endif