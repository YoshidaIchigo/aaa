#pragma once
#include"Geometory.h"
#include<DirectXMath.h>
class Wedge
{
public:
	Wedge();
	~Wedge();
	void Update();
	void Draw();
	void Spawn(DirectX::XMFLOAT3 pos);
	Info GetInfo();
	bool IsUse();
	void Trigger();
private:
	Info m_info;
	bool m_bUse=false;
	bool m_bTrigger=false;
	float m_life=0.0f;
};

