#include "ShaderManager.h"
#include <boost/foreach.hpp>
#include <vector>
#include "Engine.h"

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
	RemoveAllInputLayouts();
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

bool ShaderManager::GenerateInputLayoutFromVertexShader(ID3DBlob* pVertexShaderBlob, ID3D11InputLayout** pInputLayout)
{
	HRESULT hr = S_OK;

	// Reflect shader info to retreive the metadata of the shader
    ID3D11ShaderReflection* pVertexShaderReflection = NULL; 
	hr = D3DReflect( pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &pVertexShaderReflection );
    if (FAILED(hr))
    {
        return false;
    }

	//Retreives the shader info from the shader
	D3D11_SHADER_DESC vertexShaderDesc;
	hr = pVertexShaderReflection->GetDesc(&vertexShaderDesc);
	if (FAILED(hr))
    {
        return false;
    }

	// Read input layout description from shader info
    UINT byteOffset = 0;
    vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for ( UINT i=0; i< vertexShaderDesc.InputParameters; i++ )
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;       
        pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc );
 
        // fill out input element desc
        D3D11_INPUT_ELEMENT_DESC elementDesc;   
        elementDesc.SemanticName = paramDesc.SemanticName;      
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = byteOffset;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;   
 
        /* determine DXGI format
		 * The Mask in the D3D11_SIGNATURE_PARAMETER_DESC determines how many components there are in the used type.
		 * So we have to check the bits of the mask (0001 = 1, 0011, = 2, 0111 = 3, 1111 = 4)
		 * The ComponentType tells us which actual type is used.
		*/
        if ( paramDesc.Mask == 1 ) //Only one Component, so _R32_ in the format
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
            byteOffset += 4;
        }
        else if ( paramDesc.Mask <= 3 ) //Two Components, so _R32G32_ in the format
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
            byteOffset += 8;
        }
        else if ( paramDesc.Mask <= 7 )//Three Components, so _R32G32B32_ in the format
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            byteOffset += 12;
        }
        else if ( paramDesc.Mask <= 15 )//Four Components, so _R32G32B32A32_ in the format
        {
            if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            byteOffset += 16;
        }
             
        //save element desc
        inputLayoutDesc.push_back(elementDesc);
    }       
 
	//ENGINE->GetDevice()->g;
    // Try to create Input Layout
	hr = ENGINE->GetDevice()->Get3DDevice()->CreateInputLayout( &inputLayoutDesc[0], inputLayoutDesc.size(), pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), pInputLayout );
 
    //Free allocation shader reflection memory
    pVertexShaderReflection->Release();
	return SUCCEEDED(hr);
}
/*
bool ShaderManager::GenerateConstantBufferFromShader(ID3DBlob* pVertexShaderBlob)
{
	HRESULT hr = S_OK;

	// Reflect shader info to retreive the metadata of the shader
    ID3D11ShaderReflection* pVertexShaderReflection = NULL; 
	hr = D3DReflect( pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &pVertexShaderReflection );
    if (FAILED(hr))
    {
        return false;
    }

	//Retreives the shader info from the shader
	D3D11_SHADER_DESC vertexShaderDesc;
	hr = pVertexShaderReflection->GetDesc(&vertexShaderDesc);
	if (FAILED(hr))
    {
        return false;
    }

	// Read constant buffer description from shader info
    UINT byteOffset = 0;
    vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for ( UINT i=0; i< vertexShaderDesc.ConstantBuffers; i++ )
    {
        ID3D11ShaderReflectionConstantBuffer* constantBuffer = pVertexShaderReflection->GetConstantBufferByIndex(i);
		
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		constantBuffer->GetDesc(&bufferDesc);
		//
		for ( UINT i=0; i< bufferDesc.Variables; i++ )
		{
			ID3D11ShaderReflectionVariable* shaderVariable = constantBuffer->GetVariableByIndex(i);
		}

	}
}
*/
void ShaderManager::AddInputLayout(const tstring& inputLayoutName, ID3D11InputLayout* inputLayout)
{
	m_InputLayouts[inputLayoutName] = inputLayout;
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

ID3D11InputLayout* ShaderManager::GetInputLayout(const tstring& inputLayoutName)
{
	return m_InputLayouts[inputLayoutName];
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

bool ShaderManager::IsVertexShaderPresent(const tstring& vShaderName)
{
	map<tstring,ID3D11VertexShader*>::iterator pos = m_VertexShaders.find(vShaderName);
	return (pos != m_VertexShaders.end());
}

bool ShaderManager::IsPixelShaderPresent(const tstring& pShaderName)
{
	map<tstring,ID3D11PixelShader*>::iterator pos = m_PixelShaders.find(pShaderName);
	return (pos != m_PixelShaders.end());
}

bool ShaderManager::IsGeometryShaderPresent(const tstring& gShaderName)
{
	map<tstring,ID3D11GeometryShader*>::iterator pos = m_GeometryShaders.find(gShaderName);
	return (pos != m_GeometryShaders.end());
}

void ShaderManager::RemoveAllInputLayouts()
{
	BOOST_FOREACH(StringInputLayoutPair &inputLayoutPair, m_InputLayouts)
	{
		D3DD11_RELEASE_AND_CLEAN(inputLayoutPair.second);
	}
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
