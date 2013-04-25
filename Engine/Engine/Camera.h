#ifndef __Camera_H_
#define __Camera_H_

#include "GeometryHelper.h"
class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Initialize(XMFLOAT3 cameraPos, XMFLOAT3 targetPos, XMFLOAT3 upVector);

	XMFLOAT4X4 GetProjection() const;
	XMFLOAT4X4 GetView() const;	  

	XMFLOAT3 GetCameraPos();
	XMFLOAT3 GetTargetPos();
	XMFLOAT3 GetUpVector();

	void SetProjection(XMFLOAT4X4 projection);
	void SetView(XMFLOAT4X4 view);	   

	void SetCameraPos(XMFLOAT3 cameraPos);
	void SetTargetPos(XMFLOAT3 targetPos);
	void SetUpVector(XMFLOAT3 upVector);

	void UpdateViewMatrix();
protected:
	//-----------------
	//Member Variables
	//-----------------
	XMFLOAT4X4 m_Projection;
	XMFLOAT4X4 m_View;

	XMFLOAT3 m_CameraPos;
	XMFLOAT3 m_TargetPos;
	XMFLOAT3 m_UpVector;

private:
	void UpdateProjectionMatrix();
	
};
#endif