#ifndef __Device_H_
#define __Device_H_

#include "Util.h"

//typedef ID3D11Device Pi3DDevice;
//Magic Numbers
const int REFRESHRATE = 60;

class Device
{
public: 
	Device(int width, int height);
	virtual ~Device(){};

	virtual bool InitDisplay() = 0;

	void SetWidth(int width);
	void SetHeight(int height);
	int GetWidth() const;
	int GetHeight() const;
	virtual void CleanUp() = 0;

	virtual void ClearRenderTargetView(const float* clearColor) = 0;
	virtual void ClearDepthStencilView() = 0;
	virtual void SetDepthStencilState() = 0;
	virtual void PresentSwapChain() = 0;

	virtual Pi3DDevice* Get3DDevice() const = 0;
	virtual Pi3DDeviceContext* GetImmediateContext() const = 0;
protected:
	int m_Width;
	int m_Height;
};
#endif