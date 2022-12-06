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
	//ビュー行列の計算
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),//カメラ座標
		DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),//注視点
		DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f) //カメラの上方向
	);
	//転置行列へ変換
	view = DirectX::XMMatrixTranspose(view);
	//XMMATRIX型からXMFLOAT4X4型(mat[0])へ変換して格納
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	//プロジェクション行列の計算
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		m_fovy,//カメラの縦方向の画角
		m_aspect,//縦幅に対する横幅の比の値
		m_near,		//写り始めの距離
		m_far		//写す限界距離
	);
	//転置行列へ変換
	proj = DirectX::XMMatrixTranspose(proj);
	//XMMATRIX型からXMFLOAT4X4型(mat[0])へ変換して格納
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}
