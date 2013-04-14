#ifndef __GeometryMesh_H_
#define __GeometryMesh_H_
#include "GeometryHelper.h"
#include "GeometryTriangles.h"

const XMVECTOR EYEVECTOR = XMVectorSet( 0.0f, 2.f, -5.0f, 0.0f );
const XMVECTOR ATVECTOR = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
const XMVECTOR UPVECTOR = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
class GeometryMesh
{
public:
	GeometryMesh();
	virtual ~GeometryMesh();
	
	void Initialize();
	virtual void Update();
	virtual void Render();

protected:

	virtual void CreateGeometry() =0;
	void InitializeBuffers();
	//-----------------
	//Member Variables
	//-----------------
	GeometryTriangles* m_pGeometryTriangles;
	GeometryBuffers m_GeometryBuffers;
};

#endif