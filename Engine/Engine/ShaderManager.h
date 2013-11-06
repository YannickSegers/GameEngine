#ifndef __ShaderManager_H_
#define __ShaderManager_H_

#include <map>
#include "Util.h"
typedef map<tstring,ID3D11InputLayout*>::value_type StringInputLayoutPair;
typedef map<tstring,ID3D11VertexShader*>::value_type StringVertexShaderPair;
typedef map<tstring,ID3D11PixelShader*>::value_type StringPixelShaderPair;
typedef map<tstring,ID3D11GeometryShader*>::value_type StringGeometryShaderPair;
/*
* Class that manages all the shaders
* Has methods for compiling and storing shader files
*/
class ShaderManager
{
public:
	ShaderManager();
	virtual ~ShaderManager();

	bool CompileShaderFromFile(const tstring& fileName, LPCSTR shaderName, LPCSTR shaderModel, ID3D10Blob** ppBlobOut);
	bool GenerateInputLayoutFromVertexShader(ID3DBlob* pVertexShaderBlob, ID3D11InputLayout** pInputLayout);

	void AddInputLayout(const tstring& inputLayoutName, ID3D11InputLayout* inputLayout);
	void AddVertexShader(const tstring& vShaderName, ID3D11VertexShader* vertexShader);
	void AddPixelShader(const tstring& pShaderName, ID3D11PixelShader* pixelShader);
	void AddGeometryShader(const tstring& gShaderName, ID3D11GeometryShader* geometryShader);

	ID3D11InputLayout* GetInputLayout(const tstring& inputLayoutName);
	ID3D11VertexShader* GetVertexShader(const tstring& vShaderName);
	ID3D11PixelShader* GetPixelShader(const tstring& pShaderName);
	ID3D11GeometryShader* GetGeometryShader(const tstring& gShaderName);

	bool IsVertexShaderPresent(const tstring& vShaderName);
	bool IsPixelShaderPresent(const tstring& pShaderName);
	bool IsGeometryShaderPresent(const tstring& gShaderName);

	void RemoveAllInputLayouts();
	void RemoveAllVertexShaders();
	void RemoveAllPixelShaders();
	void RemoveAllGeometryShaders();

protected:
	map<tstring,ID3D11InputLayout*> m_InputLayouts;
	map<tstring,ID3D11VertexShader*> m_VertexShaders;
	map<tstring,ID3D11PixelShader*> m_PixelShaders;
	map<tstring,ID3D11GeometryShader*> m_GeometryShaders;

private:
	ShaderManager(const ShaderManager& t);
	ShaderManager& operator=(const ShaderManager& t);
};
#endif