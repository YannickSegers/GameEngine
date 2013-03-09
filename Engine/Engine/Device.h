#ifndef __Device_H_
#define __Device_H_

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
	virtual void CleanUp() = 0;

	virtual void ClearRenderTargetView(const float* clearColor) = 0;
	virtual void PresentSwapChain() = 0;
protected:
	int m_Width;
	int m_Height;
};
#endif