#ifndef __Vertex_H_
#define __Vertex_H_

#include "Util.h"

struct Vertex
{
	XMFLOAT3 m_Pos;
	Vertex(float x, float y, float z): m_Pos(x,y,z)
	{
	}
};

struct VertexPosTex : Vertex
{
	XMFLOAT2 m_Tex;

	VertexPosTex(float xPos, float yPos, float zPos, float xTex, float yTex)
		: Vertex(xPos,yPos,zPos)
		, m_Tex(xTex,yTex)
	{
	}
};

// ConstantBuffer Structs
struct CBNeverChanges
{
	XMMATRIX mView;
};

struct CBChangeOnResize
{
	XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
};
#endif