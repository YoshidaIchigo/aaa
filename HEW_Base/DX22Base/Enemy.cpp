#include "Enemy.h"
#define DESTROY_COUNT (10)
Enemy::Enemy()
{
	m_info.pos = { 0.0f, 0.0f, 0.0f };
	m_info.size = { 3.0f, 3.0f, 3.0f };
	m_info.rot = { 0.0f, 0.0f, 0.0f };
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (m_bDestroy)
	{
		m_nDestroyCnt++;
		m_info.size.x += 0.2f / DESTROY_COUNT;
		m_info.size.y += 0.2f / DESTROY_COUNT;
		m_info.size.z += 0.2f / DESTROY_COUNT;
		m_info.pos.y +=3.0f/DESTROY_COUNT;
		if (m_nDestroyCnt > DESTROY_COUNT)
		{
			m_bUse = false;
		}
	}
}

void Enemy::Draw()
{
	SetGeometoryTranslate(m_info.pos);
	SetGeometoryRotation(m_info.rot);
	SetGeometoryScaling(m_info.size);
	DrawCone();
}

void Enemy::Spawn(DirectX::XMFLOAT3 pos)
{
	m_info.pos = pos;
	m_info.pos.y = 1.0f;
	m_info.size = { 3.0f, 3.0f, 3.0f };
	m_bUse = true;
	m_bDestroy = false;
}

Info Enemy::GetInfo()
{
	return m_info;
}

bool Enemy::IsUse()
{
	return m_bUse;
}

void Enemy::Destroy()
{
	m_bDestroy = true;
	m_nDestroyCnt = 0;
}
