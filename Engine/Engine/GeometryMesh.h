#ifndef __GeometryMesh_H_
#define __GeometryMesh_H_
#include "GeometryHelper.h"
#include "GeometryTriangles.h"
//struct Vertex;
//struct CBWorldViewProjection;
#include "Vertex.h"
class RenderData;

class GeometryMesh
{
public:
	GeometryMesh();
	virtual ~GeometryMesh();
	
	void Initialize();
	virtual void Update();
	virtual void Render(const RenderData* pRenderData);

protected:

	virtual void CreateGeometry() =0;
	void InitializeBuffers();
	//-----------------
	//Member Variables
	//-----------------
	GeometryTriangles* m_pGeometryTriangles;
	GeometryBuffers m_GeometryBuffers;
	XMFLOAT4X4 m_World;
};

#endif