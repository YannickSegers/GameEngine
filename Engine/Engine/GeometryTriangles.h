#ifndef __GeometryTriangles_H_
#define __GeometryTriangles_H_

#include <vector>
#include "Vertex.h"

//template<typename T = Vertex>
class GeometryTriangles
{
public:
	GeometryTriangles();
	~GeometryTriangles();

	void AddTriangle( int index0, int index1, int index2 );
	int AddVertex(Vertex vertex);
	Vertex* GetVertexAtIndex( int index );
	const vector<Vertex>& GetVertices() const;
	const vector<int>& GetIndices() const;

private:
	vector<Vertex>	m_Vertices;
	vector<int> m_Indices;
};

#endif