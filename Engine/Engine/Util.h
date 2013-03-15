#ifndef __Util_H_
#define __Util_H_

using namespace std;

	//includes
	#include <windows.h>
	#include <d3d11.h>
	#include <d3dx11.h>
	#include <d3dcompiler.h>
	#include <xnamath.h>
	#include <cassert>
	#include <string>

#ifdef _UNICODE
	#define tstring wstring
	#define tcin wcin
	#define tcout wcout
	#define tstringstream wstringstream
	#define tostringstream wostringstream
	#define tofstream wofstream
	#define tifstream wifstream
	#define tfstream wfstream
	#define tstrtod wcstod
	#define tstrtol wcstol
	#define tchar wchar_t 
	#define tstrcmp wcscmp
	#define tstrcpy_s wcscpy_s
	#define tfopen _wfopen_s
	#define tstrtod	wcstod
	#define tof _wtof
#else
	#define tstring string
	#define tcin cin
	#define tcout cout
	#define tstringstream stringstream
	#define tostringstream ostringstream
	#define tofstream ofstream
	#define tifstream ifstream
	#define tfstream fstream
	#define tstrod strtod
	#define tstrtol strtol
	#define tchar char 
	#define tstrcmp strcmp
	#define tstrcpy_s strcpy_s
	#define tfopen fopen_s
	#define	tstrtod strtod
	#define tof atof
#endif
	
	// macro defines
	#define D3DD11_SET_DEGUG_NAME(buffer, text) {buffer->SetPrivateData( WKPDID_D3DDebugObjectName, sizeof(text)-1, text);}
	#define D3DD11_RELEASE_AND_CLEAN(p) {if(p != 0) {p->Release();p=0;}}
	#define D3DD11_DELETE_AND_CLEAN(p) {if(p != 0) {delete (p);p=0;}}
#endif