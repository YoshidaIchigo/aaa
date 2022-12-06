#pragma once
#include<DirectXMath.h>
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase(){}
	virtual void Update() = 0;

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	DirectX::XMFLOAT3 GetLook() { return m_look; }
protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//�r���[�s��̐ݒ�ɕK�v�ȕϐ�
	float m_fovy, m_aspect, m_near, m_far;	//�v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�
};

