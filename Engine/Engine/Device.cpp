#include "Device.h"

Device::Device(int width, int height)
	:m_Width(width)
	,m_Height(height)
{

}

void Device::SetWidth(int width)
{
	m_Width = width;
}

void Device::SetHeight(int height)
{
	m_Height = height;
}

int Device::GetWidth()
{
	return m_Width;
}

int Device::GetHeight()
{
	return m_Height;
}