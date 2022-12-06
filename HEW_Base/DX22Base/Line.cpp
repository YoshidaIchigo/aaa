#include"Line.h"
#include<math.h>
#define LINE_LIFE (2.0f)
Line::Line()
{
	m_info.pos = { 0.0f, 0.0f, 0.0f };
	m_info.size = { 0.5f, 0.5f, 0.5f };
	m_info.rot = { 0.0f, 0.0f, 0.0f };
}

Line::~Line()
{
}

void Line::Update()
{
	m_life -= 1.0f / 60.0f;
	if (m_life < 0.0f)
	{
		m_bUse = false;
	}
}

void Line::Draw()
{
	SetGeometoryTranslate(m_info.pos);
	SetGeometoryRotation(m_info.rot);
	SetGeometoryScaling(m_info.size);
	DrawBox();
}

void Line::Spawn(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2)
{
	m_bUse = true;
	m_life = LINE_LIFE;
	//ステータス設定
	//座標
	m_info.pos.x = (pos1.x + pos2.x)/2.0f;
	m_info.pos.y = 1.5f;
	m_info.pos.z = (pos1.z + pos2.z)/2.0f;
	//角度
	DirectX::XMVECTOR vector = { pos2.x - pos1.x ,pos2.y - pos1.y,pos2.z - pos1.z, };
	DirectX::XMFLOAT3 work;// = { pos2.x - pos1.x ,pos2.y - pos1.y,pos2.z - pos1.z, };
	DirectX::XMStoreFloat3(&work, vector);
	m_info.rot.y = atanf(work.z/-work.x);

	//大きさ
	vector = DirectX::XMVector3Length(vector);
	DirectX::XMStoreFloat( &m_info.size.x, vector);
}

Info Line::GetInfo()
{
	return m_info;
}

bool Line::IsUse()
{
	return m_bUse;
}
