#ifndef __Game_H_
#define __Game_H_

//Includes
#include "AbstractGame.h"
#include "Cube.h"
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
};
#endif