#include "RenderData.h"
RenderData::RenderData()
	:m_pCamera(0)
{

}

//Camera will not be deleted here, it will be deleted where it is initialized
RenderData::~RenderData()
{

}

void RenderData::SetCamera(Camera* camera)
{
	m_pCamera = camera;
}

Camera* RenderData::GetCamera()const
{
	return m_pCamera;
}
