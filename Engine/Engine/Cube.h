#ifndef __Cube_H_
#define __Cube_H_
#include "GeometryMesh.h"

class Cube: public GeometryMesh
{
public:
	Cube();
	virtual ~Cube();

	virtual void Update();

protected:
	virtual void CreateGeometry();
};

#endif