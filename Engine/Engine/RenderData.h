#ifndef __RenderData_H_
#define __RenderData_H_

class Camera;
class RenderData
{
public:
	RenderData();
	virtual ~RenderData();

	void SetCamera(Camera* camera);
	Camera* GetCamera() const;
private:
	Camera* m_pCamera;
};
#endif