#include "Cube.h"

Cube::Cube()
	:GeometryMesh()
{

}

Cube::~Cube()
{
	//GeometryMesh::~GeometryMesh();
	D3DD11_DELETE_AND_CLEAN(m_pGeometryTriangles);
}

void Cube::Update()
{
	GeometryMesh::Update();
}

void Cube::CreateGeometry()
{
	m_pGeometryTriangles = new GeometryTriangles();
	m_pGeometryTriangles->AddVertex( Vertex(-1.0f,  1.0f, -1.0f) ); // 0
	m_pGeometryTriangles->AddVertex( Vertex( 1.0f,  1.0f, -1.0f) ); // 1
	m_pGeometryTriangles->AddVertex( Vertex( 1.0f, -1.0f, -1.0f) ); // 2
	m_pGeometryTriangles->AddVertex( Vertex(-1.0f, -1.0f, -1.0f) ); // 3
															   
															   
	m_pGeometryTriangles->AddVertex( Vertex(-1.0f,  1.0f,  1.0f) ); // 4
	m_pGeometryTriangles->AddVertex( Vertex( 1.0f,  1.0f,  1.0f) ); // 5
	m_pGeometryTriangles->AddVertex( Vertex( 1.0f, -1.0f,  1.0f) ); // 6
	m_pGeometryTriangles->AddVertex( Vertex(-1.0f, -1.0f,  1.0f) ); // 7
								
	// back face
	m_pGeometryTriangles->AddTriangle( 0, 1, 2);
	m_pGeometryTriangles->AddTriangle( 2, 3, 0);

	// front face
	m_pGeometryTriangles->AddTriangle( 4+1, 4+0, 4+3);
	m_pGeometryTriangles->AddTriangle( 4+3, 4+2, 4+1);

	// left face
	m_pGeometryTriangles->AddTriangle( 4+0, 0+0, 0+3);
	m_pGeometryTriangles->AddTriangle( 0+3, 4+3, 4+0);

	// right face
	m_pGeometryTriangles->AddTriangle( 0+1, 4+1, 4+2);
	m_pGeometryTriangles->AddTriangle( 4+2, 0+2, 0+1);

	// top face
	m_pGeometryTriangles->AddTriangle( 4+0, 4+1, 0+1);
	m_pGeometryTriangles->AddTriangle( 0+1, 0+0, 4+0);

	// bottom face
	m_pGeometryTriangles->AddTriangle( 0+2, 4+2, 4+3);
	m_pGeometryTriangles->AddTriangle( 4+3, 0+3, 0+2);
}