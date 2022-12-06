#include "CameraEvent.h"
#include"easing.h"
CameraEvent::CameraEvent()
	:m_start(0.0f, 0.0f, 0.0f)
	,m_end(0.0f, 0.0f, 0.0f)
	, m_time(0.0f)
	, m_totalTime(0.0f)
{
}

void CameraEvent::Update()
{
	if (!IsEvent()) { return; }
	/*メンバー変数を用いて、カメラの注視点を補間*/
	m_look.x = (m_end.x - m_start.x)*BackEaseOut( m_time / m_totalTime) + m_start.x;
	m_look.y= (m_end.y - m_start.y)*BackEaseOut(m_time / m_totalTime) + m_start.y;
	m_look.z = (m_end.z - m_start.z)*BackEaseOut(m_time / m_totalTime) + m_start.z;
	/*注視点を元にカメラの位置を決める*/
	m_pos = m_look;
	m_pos.y += 1.0f;
	m_pos.z -= 4.0f;
	m_time += 1.0f / 60.0f;
}

void CameraEvent::SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time)
{
	m_start = startPos;
	m_end = endPos;
	m_time = 0.0f;
	m_totalTime = time;
}
