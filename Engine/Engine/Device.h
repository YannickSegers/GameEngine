#ifndef __Device_H_
#define __Device_H_

class Device
{
public: 
	Device(int width, int height);
	virtual ~Device(){};

	virtual bool InitDisplay() = 0;

	void SetWidth(int width);
	void SetHeight(int height);

protected:
	int m_Width;
	int m_Height;
};
#endif