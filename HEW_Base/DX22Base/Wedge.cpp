#include "Wedge.h"
#define WEDGE_LIFE (2.0f);
Wedge::Wedge()
{
	m_info.pos = { 0.0f, 0.0f, 0.0f };
	m_info.size = { 1.0f, 5.0f, 1.0f };
	m_info.rot = { 0.0f, 0.0f, 0.0f };
}

Wedge::~Wedge()
{
}

void Wedge::Update()
{
	if (m_bTrigger)
	{
		m_life -= 1.0f / 60.0f;
		if (m_life < 0)
		{
			m_bUse = false;
		}
	}
}

void Wedge::Draw()
{
	SetGeometoryTranslate(m_info.pos);
	SetGeometoryRotation(m_info.rot);
	SetGeometoryScaling(m_info.size);
	DrawCylinder();
}

void Wedge::Spawn(DirectX::XMFLOAT3 pos)
{
	m_info.pos = pos;
	m_info.pos.y = 0.0f;
	m_bUse = true;
	m_bTrigger = false;
}

Info Wedge::GetInfo()
{
	return m_info;
}

bool Wedge::IsUse()
{
	return m_bUse;
}

void Wedge::Trigger()
{
	m_bTrigger = true;
	m_life = WEDGE_LIFE;
}
