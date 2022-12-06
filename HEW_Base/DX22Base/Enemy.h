#pragma once
#include"Geometory.h"
#include<DirectXMath.h>
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Draw();
	void Spawn(DirectX::XMFLOAT3 pos);
	Info GetInfo();
	bool IsUse();
	void Destroy();
private:
	Info m_info;
	bool m_bUse = false;
	bool m_bDestroy = false;
	int m_nDestroyCnt = 0;
	float m_life = 0.0f;
};

