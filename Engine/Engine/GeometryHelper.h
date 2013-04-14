#ifndef __GeometryHelper_H_
#define __GeometryHelper_H_

#include "Util.h"
//#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dcompiler.h>

struct GeometryBuffers
{
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	UINT m_NumIndices;
	ID3D11Buffer* m_pCBChangesEveryFrame;
	ID3D11Buffer* m_pCBNeverChanges;
	ID3D11Buffer* m_pCBChangeOnResize;

	GeometryBuffers()
		:m_pVertexBuffer(0)
		,m_pIndexBuffer(0)
		,m_NumIndices(0)
		,m_pCBChangesEveryFrame(0)
		,m_pCBNeverChanges(0)
		,m_pCBChangeOnResize(0)
	{

	}

	~GeometryBuffers()
	{
		 D3DD11_RELEASE_AND_CLEAN(m_pVertexBuffer);
		 D3DD11_RELEASE_AND_CLEAN(m_pIndexBuffer);
		 D3DD11_RELEASE_AND_CLEAN(m_pCBChangesEveryFrame);
		 D3DD11_RELEASE_AND_CLEAN(m_pCBNeverChanges);
		 D3DD11_RELEASE_AND_CLEAN(m_pCBChangeOnResize);
	}
};

#endif