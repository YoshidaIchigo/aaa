#include "CameraPlayer.h"
#include"Input.h"
const float PCAMERA_ROTATE_SPEAD = 0.01f;
const float PCAMERA_MOVE_SPEAD = 0.1f;
CameraPlayer::CameraPlayer(Player * pPlayer)
	:m_pPlayer(pPlayer)
{

	m_radXZ = m_lateXZ = 3.14f*1.0f;
	m_radY = m_lateY = 3.14f*0.2f;
	m_radius = 8.0f;
}

void CameraPlayer::Update()
{
	m_look = m_pPlayer->GetPos();
	//W,A,S,D,Q,Eでカメラの位置を動かす
	if (IsKeyPress(VK_UP))m_radY += PCAMERA_ROTATE_SPEAD;
	if (IsKeyPress(VK_DOWN))m_radY -= PCAMERA_ROTATE_SPEAD;
	if (IsKeyPress(VK_RIGHT))m_radXZ += PCAMERA_ROTATE_SPEAD * 3;
	if (IsKeyPress(VK_LEFT))m_radXZ -= PCAMERA_ROTATE_SPEAD * 3;
	if (IsKeyPress(VK_RSHIFT))m_radius += PCAMERA_MOVE_SPEAD;
	if (IsKeyPress(VK_RCONTROL))m_radius -= PCAMERA_MOVE_SPEAD;
	//遅れていく場合の角度を計算
	m_lateXZ = (m_radXZ - m_lateXZ)*0.1f + m_lateXZ;
	m_lateY = (m_radY - m_lateY)*0.1f + m_lateY;

	m_pos.x = cosf(m_lateY)*sinf(m_lateXZ)*m_radius + m_look.x;
	m_pos.y = sinf(m_lateY)*m_radius + m_look.y;
	m_pos.z = cosf(m_lateY)*cosf(m_lateXZ)*m_radius + m_look.z;
}
