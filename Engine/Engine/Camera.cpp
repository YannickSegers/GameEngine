#include "Camera.h"
#include "Engine.h"

Camera::Camera()
{
	XMMATRIX identity = XMMatrixIdentity();
	XMStoreFloat4x4(&m_Projection,identity);
	XMStoreFloat4x4(&m_View,identity);
}

Camera::~Camera()
{

}

void Camera::Initialize(XMFLOAT3 cameraPos, XMFLOAT3 targetPos, XMFLOAT3 upVector)
{
	SetCameraPos(cameraPos);
	SetTargetPos(targetPos);
	SetUpVector(upVector);
	UpdateProjectionMatrix();
	UpdateViewMatrix();
}

XMFLOAT4X4 Camera::GetProjection() const
{
	return m_Projection;
}

XMFLOAT4X4 Camera::GetView() const
{
	return m_View;
}

XMFLOAT3 Camera::GetCameraPos() const
{
	return m_CameraPos;
}

XMFLOAT3 Camera::GetTargetPos() const
{
	return m_TargetPos;
}

XMFLOAT3 Camera::GetUpVector() const
{
	return m_UpVector;
}

void Camera::SetProjection(XMFLOAT4X4 projection)
{
	m_Projection = projection;
}

void Camera::SetView(XMFLOAT4X4 view)
{
	m_View = view;
}
	   
void Camera::SetCameraPos(XMFLOAT3 cameraPos)
{
	m_CameraPos = cameraPos;
}

void Camera::SetTargetPos(XMFLOAT3 targetPos)
{
	m_TargetPos = targetPos;
}

void Camera::SetUpVector(XMFLOAT3 upVector)
{
	m_UpVector = upVector;
}

void Camera::UpdateProjectionMatrix()
{
	XMMATRIX projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, ENGINE->GetDevice()->GetWidth() / (FLOAT)ENGINE->GetDevice()->GetHeight(), 0.01f, 100.0f ); 
	XMStoreFloat4x4(&m_Projection,projection); 
}

void Camera::UpdateViewMatrix()
{
	XMMATRIX view = XMMatrixLookAtLH(XMLoadFloat3(&m_CameraPos),XMLoadFloat3(&m_TargetPos), XMLoadFloat3(&m_UpVector) );
	XMStoreFloat4x4(&m_View,view); 
}