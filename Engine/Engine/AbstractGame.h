#ifndef __AbstractGame_H_
#define __AbstractGame_H_

class AbstractGame
{
public:
	AbstractGame(){};
	virtual ~AbstractGame(){};

	virtual void InitializeElements() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};
#endif