#include "ShaderManager.h"
#include <boost/foreach.hpp>

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
	RemoveAllVertexShaders();
	RemoveAllPixelShaders();
	RemoveAllGeometryShaders();
}

bool ShaderManager::CompileShaderFromFile(const tstring& fileName, LPCSTR shaderName, LPCSTR shaderModel, ID3D10Blob** ppBlobOut)
{
	HRESULT hr = S_OK;
	
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		shaderFlags |= D3DCOMPILE_DEBUG;
	#endif

	ID3DBlob* pErrorBlob = 0;
	hr = D3DX11CompileFromFile(fileName.c_str(), 0, 0, shaderName, shaderModel, shaderFlags, 0, 0, ppBlobOut, 0, 0);

	#if defined( DEBUG ) || defined( _DEBUG )
		if( FAILED(hr) )
		{
			if( pErrorBlob != NULL )
				OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );	
		}
	#endif

	if( pErrorBlob ) pErrorBlob->Release();
	return SUCCEEDED(hr);
}

void ShaderManager::AddVertexShader(const tstring& vShaderName, ID3D11VertexShader* vertexShader)
{
	m_VertexShaders[vShaderName] = vertexShader;
}

void ShaderManager::AddPixelShader(const tstring& pShaderName, ID3D11PixelShader* pixelShader)
{
	m_PixelShaders[pShaderName] = pixelShader;
}

void ShaderManager::AddGeometryShader(const tstring& gShaderName, ID3D11GeometryShader* geometryShader)
{
	m_GeometryShaders[gShaderName] = geometryShader;
}

ID3D11VertexShader* ShaderManager::GetVertexShader(const tstring& vShaderName)
{
	return m_VertexShaders[vShaderName];
}

ID3D11PixelShader* ShaderManager::GetPixelShader(const tstring& pShaderName)
{
	return m_PixelShaders[pShaderName];
}

ID3D11GeometryShader* ShaderManager::GetGeometryShader(const tstring& gShaderName)
{
	return m_GeometryShaders[gShaderName];
}

bool ShaderManager::isVertexShaderPresent(const tstring& vShaderName)
{
	map<tstring,ID3D11VertexShader*>::iterator pos = m_VertexShaders.find(vShaderName);
	return (pos != m_VertexShaders.end());
}

bool ShaderManager::isPixelShaderPresent(const tstring& pShaderName)
{
	map<tstring,ID3D11PixelShader*>::iterator pos = m_PixelShaders.find(pShaderName);
	return (pos != m_PixelShaders.end());
}

bool ShaderManager::isGeometryShaderPresent(const tstring& gShaderName)
{
	map<tstring,ID3D11GeometryShader*>::iterator pos = m_GeometryShaders.find(gShaderName);
	return (pos != m_GeometryShaders.end());
}

//Removes all the vertex shaders
void ShaderManager::RemoveAllVertexShaders()
{
	BOOST_FOREACH(StringVertexShaderPair &vertexShaderPair, m_VertexShaders)
	{
		D3DD11_RELEASE_AND_CLEAN(vertexShaderPair.second);
	}
}

void ShaderManager::RemoveAllPixelShaders()
{
	BOOST_FOREACH(StringPixelShaderPair &pixelShaderPair, m_PixelShaders)
	{
		D3DD11_RELEASE_AND_CLEAN(pixelShaderPair.second);
	}
}

void ShaderManager::RemoveAllGeometryShaders()
{
	BOOST_FOREACH(StringGeometryShaderPair &geometryShaderPair, m_GeometryShaders)
	{
		D3DD11_RELEASE_AND_CLEAN(geometryShaderPair.second);
	}
}
