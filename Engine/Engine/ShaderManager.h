#ifndef __ShaderManager_H_
#define __ShaderManager_H_

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

protected:
};
#endif