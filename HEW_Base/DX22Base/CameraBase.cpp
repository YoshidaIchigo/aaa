#include "CameraBase.h"

CameraBase::CameraBase()
	:m_pos(0.0f, 0.0f, -7.0f)
	,m_look(0.0f, 0.0f, 0.0f)
	,m_up(0.0f, 1.0f, 0.0f)
	,m_fovy(3.14f/3.0f)
	,m_aspect(16.0f/9.0f)
	,m_near(0.2f)
	,m_far(1000.0f)
{
}

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	//�r���[�s��̌v�Z
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),//�J�������W
		DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),//�����_
		DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f) //�J�����̏����
	);
	//�]�u�s��֕ϊ�
	view = DirectX::XMMatrixTranspose(view);
	//XMMATRIX�^����XMFLOAT4X4�^(mat[0])�֕ϊ����Ċi�[
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	//�v���W�F�N�V�����s��̌v�Z
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		m_fovy,//�J�����̏c�����̉�p
		m_aspect,//�c���ɑ΂��鉡���̔�̒l
		m_near,		//�ʂ�n�߂̋���
		m_far		//�ʂ����E����
	);
	//�]�u�s��֕ϊ�
	proj = DirectX::XMMatrixTranspose(proj);
	//XMMATRIX�^����XMFLOAT4X4�^(mat[0])�֕ϊ����Ċi�[
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}
