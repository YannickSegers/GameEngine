#include "GeometryTriangles.h"
#include "Util.h"


GeometryTriangles::GeometryTriangles()
{

}

GeometryTriangles::~GeometryTriangles()
{
	
}

void GeometryTriangles::AddTriangle( int index0, int index1, int index2 )
{
	m_Indices.push_back(index0);
	m_Indices.push_back(index1);
	m_Indices.push_back(index2);
}

int GeometryTriangles::AddVertex(Vertex vertex)
{
	m_Vertices.push_back(vertex);
	return m_Vertices.size() -1;
}

Vertex* GeometryTriangles::GetVertexAtIndex( int index )
{
	return &m_Vertices.at(index);
}

const vector<Vertex>& GeometryTriangles::GetVertices()
{
	return m_Vertices;
}

const vector<int>& GeometryTriangles::GetIndices()
{
	return m_Indices;
}