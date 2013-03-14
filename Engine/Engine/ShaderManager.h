#ifndef __ShaderManager_H_
#define __ShaderManager_H_

#include <map>
#include "Util.h"
/*
* Class that manages all the shaders
* Has methods for compiling and storing shader files
*/
class ShaderManager
{
public:
	ShaderManager();
	virtual ~ShaderManager();

	// GetShader();
	bool CompileShaderFromFile();

	void AddVertexShader();
	void AddPixelShader();
	void AddGeometryShader();

protected:
	map<tstring,ID3D11VertexShader> m_VertexShaders;
	map<tstring,ID3D11PixelShader> m_PixelShaders;
	map<tstring,ID3D11GeometryShader> m_GeometryShaders;
};
#endif