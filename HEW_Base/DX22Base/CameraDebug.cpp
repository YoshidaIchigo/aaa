#include "CameraDebug.h"
#include"Input.h"
const float CAMERA_MOVE_SPEAD = 0.1f;
const float CAMERA_ROTATE_SPEAD = 0.01f;
CameraDebug::CameraDebug()
{
	m_look = { 0.0f,0.0f,0.0f };
	m_radXZ = 3.14f*0.0f;
	m_radY = 3.14f*0.3f;
	m_radius = 2.0f;
}
void CameraDebug::Update()
{
	//←,↑,→,↓,Shift,Ctrlでカメラの注視点を動かす
	if (IsKeyPress(VK_UP))		m_look.z += CAMERA_MOVE_SPEAD;
	if (IsKeyPress(VK_DOWN))	m_look.z -= CAMERA_MOVE_SPEAD;
	if (IsKeyPress(VK_RIGHT))	m_look.x += CAMERA_MOVE_SPEAD;
	if (IsKeyPress(VK_LEFT))	m_look.x -= CAMERA_MOVE_SPEAD;
	if (IsKeyPress(VK_RSHIFT))	m_look.y += CAMERA_MOVE_SPEAD;
	if (IsKeyPress(VK_RCONTROL))m_look.y -= CAMERA_MOVE_SPEAD;

	//W,A,S,D,Q,Eでカメラの位置を動かす
	if (IsKeyPress('W'))m_radY += CAMERA_ROTATE_SPEAD;
	if (IsKeyPress('S'))m_radY -= CAMERA_ROTATE_SPEAD;
	if (IsKeyPress('D'))m_radXZ += CAMERA_ROTATE_SPEAD*3;
	if (IsKeyPress('A'))m_radXZ -= CAMERA_ROTATE_SPEAD*3;

	if (IsKeyPress('Q'))m_radius += CAMERA_MOVE_SPEAD;
	if (IsKeyPress('E'))m_radius -= CAMERA_MOVE_SPEAD;
	if (m_radius < 0)m_radius = 0;

	m_pos.x = cosf(m_radY)*sinf(m_radXZ)*m_radius + m_look.x;
	m_pos.y = sinf(m_radY)* m_radius + m_look.y;
	m_pos.z = cosf(m_radY)*cosf(m_radXZ)*m_radius + m_look.z;
}