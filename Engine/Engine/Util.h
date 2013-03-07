#ifndef __Util_H_
#define __Util_H_
	//includes
	#include <windows.h>
	#include <d3d11.h>
	#include <d3dx11.h>
	#include <d3dcompiler.h>
	#include <xnamath.h>
	#include <cassert>
	
	// macro defines
	#define D3DD11_SET_DEGUG_NAME(buffer, text) {buffer->SetPrivateData( WKPDID_D3DDebugObjectName, sizeof(text)-1, text);}
	#define D3DD11_RELEASE_AND_CLEAN(a) {if(a != 0) {a->Release();a=0;}}
#endif